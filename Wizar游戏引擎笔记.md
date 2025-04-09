# Wizar游戏引擎笔记

## 事件系统计划

### Application

接收事件

### Window类与Application的通信

在Window类中创建一些方法,将所有事件发回Application。

当事件发生时,window类会接收来自window的事件回调,然后window类将此事件构造成为一个Hazel事件传递回Application。

Application通过函数指针感知window发生的事件

window上设置事件侦听器的接口，每次事件发生时通过IEventListens集合然后调用OnEvent

## 事件系统

### 事件分类枚举设计

使用位字段设计的目的,能够将一个事件分成多个分类,比如:键盘事件是键盘和输入事件

```c++
#define BIT(x)  (1 << x)
enum EventCategory
{
	None = 0,
	EventCategoryApplication	= BIT(0),
	EventCategoryInput			= BIT(1),
	EventCategoryKeyboard		= BIT(2),
	EventCategoryMouse			= BIT(3),
	EventCategoryMouseButton	= BIT(4),
};
```



### protected:

只有派生类可以使用

### 事件分发机制的实现

```c++
bool Dispatch(EventFn<T> func)
{
	if (m_Event.GetEventType() == T::GetStaticType())
	{
		m_Event.m_Handled = func(*(T*)&m_Event);
		return true;
	}
	return false;
}
```

1. **函数模板**：`Dispatch` 是一个模板函数，接受一个函数对象 `func` 作为参数，这个参数的类型是 `EventFn<T>`，通常是一个函数指针、lambda 表达式或者函数对象，用于处理特定类型的事件。

2. **类型匹配检查**：

   ```cpp
   cpp复制代码
   
   if (m_Event.GetEventType() == T::GetStaticType())
   ```

   这行代码检查当前事件 `m_Event` 的类型是否和模板参数 `T` 的静态类型一致。`T::GetStaticType()` 通常是一个静态方法，用于返回某种类型标识（可能是枚举值或整数），而 `m_Event.GetEventType()` 获取当前存储的事件类型。

   只有当事件类型匹配时，才会执行后续的逻辑。

3. **事件处理**：

   ```cpp
   cpp复制代码
   
   m_Event.m_Handled = func(*(T*)&m_Event);
   ```

   如果事件类型匹配，将 `m_Event` 强制类型转换为 `T*`，然后解引用为 `T` 对象，将其作为参数传递给处理函数 `func`。

   `func` 的返回值（通常是布尔值）会被赋值给 `m_Event.m_Handled`，表示该事件是否被成功处理。

4. **返回值**：

   - 如果事件类型匹配，则函数返回 `true`。
   - 如果事件类型不匹配，则直接返回 `false`。

## 预编译头

预编译文件,准备一个.h与.cpp(mvsc编译器需要)

示例:![1742698487496](C:\Users\1207\AppData\Roaming\Typora\typora-user-images\1742698487496.png)

```c++
#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef HZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // HZ_PLATFORM_WINDOWS


```



### premake5.lua

添加以下两行,除mvsc编译器,其他编译器会自行忽略pchsource行

![1742698416603](C:\Users\1207\AppData\Roaming\Typora\typora-user-images\1742698416603.png)

### vs2022配置

![1742698593186](C:\Users\1207\AppData\Roaming\Typora\typora-user-images\1742698593186.png)

![1742698619221](C:\Users\1207\AppData\Roaming\Typora\typora-user-images\1742698619221.png)

## 窗口抽象和GLFW

### 断言宏

```c++
#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x,...) { if(!(x)){HZ_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}}
#define HZ_CORE_ASSERT(x,...) { if(!(x)){HZ_CORE_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}}
#else
#define HZ_ASSERT(x,...) 
#define HZ_CORE_ASSERT(x,...) 
#endif
```

**宏定义：**

 ` #define HZ_ASSERT(x,...) ：` 定义一个名为`HZ_ASSERT`  的宏，它接受一个布尔表达式`  x`  和可变参数

  ...  。

  - 如果表达式`x`为假（即`!(x)`为真），则执行以下操作：

    - 调用`HZ_ERROR`函数（假设已定义），并传入一个格式化字符串`"Assertion Failed :{0}"`和可变参数`__VA_ARGS__`。这里`{0}`是一个占位符，用于替换`__VA_ARGS__`中的第一个参数。
    - 调用`__debugbreak()`函数（假设已定义），这通常是一个断点函数，用于在调试器中暂停程序执行，以便开发者可以检查程序状态。

- `#define HZ_CORE_ASSERT(x,...)`：定义一个名为`HZ_CORE_ASSERT`的宏，其工作原理与`HZ_ASSERT`类似，但调用的是`HZ_CORE_ERROR`函数（假设已定义），用于核心代码的断言。

**条件编译的效果：**

- 如果定义了`HZ_ENABLE_ASSERTS`，则`HZ_ASSERT`和`HZ_CORE_ASSERT`宏将启用断言功能。当断言条件不满足时，会输出错误信息并触发断点。
- 如果没有定义`HZ_ENABLE_ASSERTS`，则`HZ_ASSERT`和`HZ_CORE_ASSERT`宏将被定义为空宏（即不执行任何操作）。这通常用于发布版本，以避免断言对性能的影响。

## 窗口事件

`std::bind(&Application::x, this, std::placeholders::_1)` 是 C++11 中 `std::bind` 的一个用法，用于绑定一个成员函数到一个特定的对象实例上。

1. **&Application::x**
   这里表示类 `Application` 的成员函数 `x` 的地址。
2. **this**
   使用 `this` 指针将成员函数绑定到当前对象实例上，表示调用 `x` 函数时，会作用于当前对象。
3. **std::placeholders::_1**
   占位符 `_1` 表示将来调用这个绑定函数时，`x` 函数的第一个参数将由调用者传入。

------

### **data.EventCallback(event); 与 BIND_EVENT_FN(OnEvent) 的关系**

**1. data.EventCallback(event)**

`data.EventCallback` 是一个函数对象（或者回调函数指针）。它被用来在事件发生时调用相应的回调函数。

- `event` 是事件参数，描述了触发事件的具体信息。
- `EventCallback` 的类型通常是某种泛型接口，比如 `std::function<void(const Event&)>` 或一个函数指针类型。

调用 `data.EventCallback(event)` 的含义是：**执行之前通过 SetEventCallback 注册的事件处理函数**，并将 `event` 对象作为参数传递给它。

**2. 关系**

以下是它们之间的关系和工作流程：

1. `BIND_EVENT_FN(OnEvent)` 将 `OnEvent` 函数绑定为一个回调函数，并返回这个回调的句柄。
2. `m_Window->SetEventCallback(...)` 将绑定后的回调函数注册到 `m_Window` 对象中。
3. 当事件发生时，`m_Window`（或其内部机制）会调用 `data.EventCallback(event)`，从而触发 `OnEvent` 函数。

简而言之：

- `BIND_EVENT_FN(OnEvent)` 负责将事件处理函数包装成回调。
- `SetEventCallback` 负责存储回调。
- `data.EventCallback(event)` 负责在事件触发时调用存储的回调。

**为什么这样使用？**

1. 解耦：
   - 事件触发逻辑（通常在底层框架中）与事件处理逻辑（由用户定义）是分离的。
   - 用户只需要提供回调函数，而不需要关心事件的具体触发机制。
2. 灵活性：
   - 可以动态更改事件处理函数，而不需要重新编译或硬编码逻辑。
   - 支持不同类型的事件处理函数（普通函数、成员函数、Lambda 等）。
3. 代码复用：
   - `BIND_EVENT_FN` 宏和回调机制可以应用于不同的事件和上下文，而无需重复代码。
4. 事件驱动编程：
   - 这种模式允许程序以事件为中心，通过回调函数响应事件，更符合 GUI 或游戏开发的常见需求。

------

**总结**

- `BIND_EVENT_FN(OnEvent)` 是一个宏（或函数），用于将事件处理函数 `OnEvent` 绑定为特定的回调函数格式。
- `m_Window->SetEventCallback(...)` 将回调函数注册到窗口对象中。
- 当事件发生时，框架会调用 `data.EventCallback(event)`，从而间接调用 `OnEvent`。
- 这种设计解耦了事件触发和事件处理，使代码更灵活、易扩展，并符合事件驱动编程范式。

### 事件分发器的作用机制

案例:

```c++
void Application::OnEvent(Event& e) 
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
}
```

**1. EventDispatcher dispatcher(e);**

- 作用：
  - 创建一个 `EventDispatcher` 对象，并将事件 `e` 传递给它。
  - `e` 是一个 `Event` 类型的引用，表示当前触发的事件。
- 内部机制：
  - `EventDispatcher` 的构造函数将 `e` 引用赋值给其私有成员 `m_Event`。
  - 这样，`dispatcher` 对象就可以访问和操作 `e`。

------

**2. dispatcher.Dispatch<WindowCloseEvent>BIND_EVENT_FN(OnWindowClosed));**

- 作用：
  - 调用 `dispatcher` 的 `Dispatch` 方法，尝试将事件 `e` 分发为 `WindowCloseEvent` 类型，并使用 `OnWindowClosed` 函数作为处理函数。
- 步骤：
  1. 事件类型检查：
     - `Dispatch<WindowCloseEvent>` 会检查 `m_Event` 的类型是否为 `WindowCloseEvent`。
     - 这是通过比较 `m_Event.GetEventType()` 和 `WindowCloseEvent::GetStaticType()` 实现的。
  2. 事件处理：
     - 如果事件类型是 `WindowCloseEvent`，则将 `m_Event` 转换为 `WindowCloseEvent` 类型，并调用处理函数 `OnWindowClosed`。
     - `func(*(T*)&m_Event)` 中的 `*(T*)&m_Event` 是一种类型转换，将基类 `Event` 引用 `m_Event` 转换为派生类 `WindowCloseEvent` 的引用。
     - 处理函数的返回值（`bool`）会被赋值给 `m_Event.m_Handled`，表示事件是否被成功处理。
  3. 返回值：
     - 如果事件类型匹配，`Dispatch` 返回 `true`，否则返回 `false`。
- `BIND_EVENT_FN(OnWindowClosed)`：
  - 宏展开为 `std::bind(&Application::OnWindowClosed, this, std::placeholders::_1)`。
  - 这会创建一个可调用对象，当调用它时，会调用 `Application` 类的 `OnWindowClosed` 成员函数，并将事件参数传递给它。

------

**总结**

- `EventDispatcher dispatcher(e);`：
  - 创建一个 `EventDispatcher` 对象，准备分发事件 `e`。
- `dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));`：
  - 检查事件 `e` 是否为 `WindowCloseEvent` 类型。
  - 如果是，则调用 `OnWindowClosed` 函数来处理事件。
  - 处理结果（`true` 或 `false`）被用来标记事件是否被成功处理。

这种设计模式可以非常灵活和模块化的方式处理不同类型的事件，而不需要在事件分发器中硬编码具体的事件处理逻辑。

## Layers

### vector::emplace

`emplace` 函数是 C++11 引入的标准库容器（如 `std::vector`, `std::deque`, `std::list`, `std::set`, `std::map` 等）中的一个成员函数，用于在容器中原地构造元素。与 `insert` 或 `push_back` 等函数相比，`emplace` 可以在不创建临时对象的情况下直接在容器的目标位置构造对象，从而提高性能。

#### `emplace` 的作用

1. **原地构造**：`emplace` 允许你在容器的指定位置直接构造对象，而不需要先创建对象再复制或移动到容器中。这意味着可以减少不必要的对象拷贝或移动操作，提高程序的效率。
2. **灵活性**：`emplace` 接受与构造函数相同的参数，因此可以灵活地构造各种类型的对象。
3. **性能优化**：通过避免不必要的临时对象创建和复制，`emplace` 可以提供比 `insert` 或 `push_back` 更好的性能，尤其是在处理大型对象或复杂对象时。

### sandbox 中的函数和 项目Nut ( Hazel ) 有什么关系?

他们是怎样传递的？ 在代码中，Sandbox 类的构造函数 

```c++
Sandbox() { 
	PushLayer(new ExampleLayer()); 
} 
```

通过 PushLayer ( ) 创建 ExampleLayer 图层对象并将其添加到 LayerStack 中， 

（而且 PushLayer 函数是 Nut 项目中 LayerStack 类中的一个函数） 

#### 这些函数是怎样能够影响到 application 中的函数的？ 

在项目 Sandbox 中，ExampleLayer 这个类继承自 Hazel::Layer，并且重写了 OnUpdate 和 OnEvent 函数。 

**这意味着**当你创建 ExampleLayer 对象并将其添加到 LayerStack 中后，这些重写的函数会在你对 ExampleLayer 对象进行操作时被"对应的"调用 

（因为在 ExampleLayer 中，这几个函数被重写了，并且作为 ExampleLayer 这个类的成员函数） 

比如在 application.cpp 中，(*--iter)->OnEvent(e); 就是自动辨别 iter 的类型，然后自动的使用了这个类下的成员函数 OnEvent 

#### 总结

所以，在 Application 类的 Run 函数中，你遍历 m_LayerStack 并调用其每个图层的 OnUpdate 函数。 

但是由于 ExampleLayer 是 Layer 的子类，所以当你对刚才传入的 LayerStack 的 ExampleLayer 类型的对象进行操作时，ExampleLayer 中重写的 OnUpdate 函数会被调用。 

同样，在 Application 类的 OnEvent 函数中，你也遍历 m_LayerStack 并调用每个图层的 OnEvent 函数。 

由于 ExampleLayer 也重写了 OnEvent 函数，所以在这里也会调用 ExampleLayer 中重写的 OnEvent 函数

## Imgui

### 单例模式（Singleton Pattern）

​	是一种创建型设计模式，它确保一个类只有一个实例，并提供一个全局访问点来访问这个实例。单例模式通常用于那些需要控制资源访问的场景，比如数据库连接、线程池、日志系统等，这些资源在整个应用程序中只需要一个共享实例。

##### 单例模式的核心要素

1. 私有构造函数：
   - 单例类的构造函数必须是私有的，以防止外部类通过构造函数创建多个实例。
2. 静态实例变量：
   - 单例类包含一个静态变量，用于保存类的唯一实例。
3. 公共静态方法：
   - 单例类提供一个公共的静态方法（通常称为`getInstance`），用于返回类的唯一实例。

### 关于WindowsWindow.cpp中的回调函数和ImGuiLayer.cpp中的OnKeyTypedEvent的关系 

为什么这两个函数有所联系？？？ 

```c++
glfwSetCharCallback( m_Window, [](GLFWwindow* window, unsigned int keycode) 

	{ 

		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 
		KeyTypedEvent event(keycode); 
		data.EventCallback(event); 
	} 
);

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) 
{ 
    ImGuiIO& io = ImGui::GetIO(); 
    int keycode = e.GetKeyCode(); 
    if (keycode > 0 && keycode < 0x10000) 
    io.AddInputCharacter((unsigned short)keycode); 	
    return false; 
} 
```

因为在回调函数glfeSetCharCallback中有通过回调函数获取的keycode构建KeyTypedEvent对象的过程 -->即 KeyTypedEvent event(keycode); 

此时我们就获取了键盘上输入的关键字，而且存入了这个事件对象中，然后在之后的ImGuiLayer上的demo窗口中，我们使用int keycode = e.GetKeyCode();获取了Keycode， 

所以相当于我们从回调函数中获取了keycode这个数据，然后在demo窗口中我们就能够使用它。

## 数学

### SIMD（Single Instruction, Multiple Data，单指令多数据流）

是一种并行计算技术，允许**一条指令同时操作多个数据元素**，显著提升特定类型计算的性能。以下是关键要点解析：

**1. 核心原理**

- **指令级并行**：通过一条指令处理多个数据（如向量运算），而非传统的一条指令处理单个数据。
- **典型场景**：多媒体处理（如图像滤镜）、科学计算（如矩阵运算）、加密/解密等涉及大量重复操作的场景。

**2. 常见指令集**



| 架构       | 指令集示例        | 特点                                   |
| ---------- | ----------------- | -------------------------------------- |
| **x86**    | SSE, AVX, AVX-512 | 支持宽向量（如AVX-512可处理512位数据） |
| **ARM**    | NEON              | 移动端高效，支持128位向量              |
| **RISC-V** | Vector扩展        | 开源灵活，适配性强                     |



**3. 编程实现方式**

- **编译器内置函数**：如`_mm_add_ps`（SSE加法）、`vld1q_u8`（NEON加载数据）。
- **自动向量化**：编译器优化（如GCC的`-O3 -ftree-vectorize`）自动将循环转换为SIMD指令。
- **手动优化**：直接编写汇编或使用Intrinsics（需熟悉指令集细节）。

**4. 性能优势示例**

假设对两个包含4个浮点数的数组进行加法：

- **传统方式**：4次循环，每次执行1次加法 → **4次指令**。
- **SIMD方式**：1次指令直接完成4对加法 → **性能提升3-4倍**（实际受内存带宽和指令延迟影响）。

**5. 注意事项**

- **数据对齐**：某些指令集要求数据按16/32字节对齐，否则触发异常。
- **指令兼容性**：不同CPU支持的SIMD指令集不同（如旧款CPU可能不支持AVX-512）。
- **Amdahl定律**：SIMD仅加速可向量化的部分，整体性能提升受限于非向量化代码比例。

**6. 检测工具**

- **CPU支持查询**：通过`/proc/cpuinfo`（Linux）或`cpuid`指令检查支持的SIMD扩展。
- **性能分析**：使用Intel VTune、Perf等工具分析向量化效率。

**7. 典型应用场景**

- **图像处理**：调整亮度、对比度（逐像素操作）。
- **机器学习**：卷积神经网络中的矩阵乘加（GEMM）。
- **物理模拟**：粒子系统中力的批量计算。

通过合理利用SIMD，开发者可以在不增加线程复杂性的前提下，显著提升计算密集型任务的效率。实际优化时需结合算法设计和硬件特性权衡。

### GLM（OpenGL Mathematics）

是一个专为图形编程设计的**开源C++数学库**，广泛应用于OpenGL/GLSL、WebGL等图形API开发中。它通过提供与GLSL（OpenGL着色器语言）高度兼容的数学接口，简化了3D图形中的向量、矩阵运算及坐标变换操作。

**核心功能与特点**

1. 数据类型丰富
   - 向量：`vec2`, `vec3`, `vec4`（支持float/double/int/uint/bool）
   - 矩阵：`mat2x2`, `mat3x3`, `mat4x4`
   - 四元数：`quat`（用于3D旋转）
   - 几何类型：`plane`, `aabb`（轴对齐包围盒）
2. 硬件兼容性设计
   - 数据布局与GLSL一致，可直接传递给着色器。
   - 支持列优先矩阵存储（符合OpenGL传统约定）。
3. 高级数学运算
   - **坐标变换**：平移、旋转、缩放、透视投影。
   - **几何计算**：点积、叉积、反射、折射。
   - **矩阵分解**：逆矩阵、转置、行列式计算。
   - **四元数插值**：球面线性插值（slerp）用于平滑动画。
4. 扩展功能
   - 噪声生成（Perlin、Simplex噪声）。
   - 几何裁剪、碰撞检测辅助函数。
   - 坐标系转换（如世界坐标→视图坐标）。

**与OpenGL的典型协作**

```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
 
// 创建模型矩阵（平移+旋转）
glm::mat4 model = glm::mat4(1.0f);
model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
 
// 创建视图矩阵（相机位置）
glm::mat4 view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 5.0f), // 相机位置
    glm::vec3(0.0f, 0.0f, 0.0f), // 目标点
    glm::vec3(0.0f, 1.0f, 0.0f)  // 上方向
);
 
// 创建投影矩阵（透视投影）
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f), // 视野角度
    800.0f / 600.0f,     // 宽高比
    0.1f,                // 近平面
    100.0f               // 远平面
);
 
// 将矩阵传递给着色器（假设已绑定uniform）
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
```

**安装与使用**

1. **安装**

   - **预编译包**：通过vcpkg、Conan或直接下载头文件。
   - **源码编译**：从GitHub克隆仓库，包含到项目路径。

2. **包含头文件**

   ```cpp
   #include <glm/glm.hpp>            // 核心功能
   #include <glm/gtc/matrix_transform.hpp> // 矩阵变换
   #include <glm/gtc/quaternion.hpp>      // 四元数支持
   ```

3. **编译选项**

   - 无需额外链接库（纯头文件实现）。
   - 可启用`GLM_FORCE_RADIANS`强制角度以弧度为单位。

**性能优化提示**

- **SIMD加速**：GLM默认利用编译器SIMD指令优化向量运算。
- **避免运行时开销**：尽量在初始化阶段计算静态变换矩阵。
- **内存对齐**：使用`glm::aligned_highp`等类型确保SIMD兼容性。

通过GLM，开发者可以更高效地处理3D数学运算，同时保持与图形API的紧密集成，是图形编程中不可或缺的工具之一。

### vcpkg 

是微软开发的一个 **跨平台 C++ 包管理工具**，支持 Windows、Linux 和 macOS，旨在简化第三方库的获取、编译和集成流程。它通过预编译的二进制文件或源码编译，帮助开发者快速管理项目依赖。

**核心功能**

1. **一键安装依赖**
   通过 `vcpkg install <库名>` 直接下载并编译库（或获取预编译二进制），自动处理依赖关系。
2. **跨平台支持**
   同一套命令可在不同操作系统上运行，生成对应平台的库文件。
3. **与 CMake 无缝集成**
   自动生成 CMake 的 `find_package` 配置，无需手动指定库路径。
4. **支持源码编译定制**
   可通过 `triplet` 文件自定义编译选项（如静态/动态链接、启用特定功能）。
5. **社区驱动**
   支持用户提交自定义端口（`port`），扩展支持的库列表。

**安装步骤**

1. **克隆仓库**

   ```bash
   git clone https://github.com/microsoft/vcpkg
   cd vcpkg
   ```

2. **运行引导脚本**

   - Windows

     （需 PowerShell 或 CMD）：

     ```bash
     bash复制代码
     
     .\bootstrap-vcpkg.bat
     ```

   - Linux/macOS

     ：

     ```bash
     bash复制代码
     
     ./bootstrap-vcpkg.sh
     ```

3. **集成到环境**（可选）

   ```bash
   bash复制代码
   
   ./vcpkg integrate install  # 全局集成（推荐）
   ```

**常用命令**

| 命令                   | 说明                      |
| ---------------------- | ------------------------- |
| `vcpkg search <库名>`  | 搜索可用的库              |
| `vcpkg install <库名>` | 安装指定库                |
| `vcpkg remove <库名>`  | 卸载指定库                |
| `vcpkg list`           | 列出已安装的库            |
| `vcpkg update`         | 更新 vcpkg 自身及端口列表 |

**使用示例（以安装 GLM 为例）**

1. **安装 GLM**

   ```bash
   bash复制代码
   
   vcpkg install glm
   ```

   - vcpkg 会自动下载源码，编译并安装到默认目录（如 `vcpkg/installed/x64-windows`）。

2. **在 CMake 项目中使用**

   ```cmake
   cmake_minimum_required(VERSION 3.14)
   project(example)
    
   find_package(glm REQUIRED)  # 自动检测 vcpkg 安装的 GLM
    
   add_executable(example main.cpp)
   target_link_libraries(example PRIVATE glm)
   ```

3. **编译项目**

   ```bash
   mkdir build
   cd build
   cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
   cmake --build .
   ```

**高级配置**

- **自定义编译选项**：通过 `triplet` 文件（如 `x64-windows-static.cmake`）指定静态链接、启用调试符号等。
- **覆盖端口行为**：在 `ports` 目录下修改或新增端口文件，定制库的编译方式。

**注意事项**

- **路径问题**：vcpkg 安装路径避免包含空格或特殊字符（如 `Program Files`）。
- **版本兼容性**：定期检查 `vcpkg update` 获取最新库版本，避免兼容性问题。
- **多实例管理**：可通过环境变量 `VCPKG_ROOT` 切换不同 vcpkg 实例。

通过 vcpkg，开发者可以专注于代码逻辑，而无需手动处理复杂的依赖管理和跨平台编译问题。

## 渲染架构

### Render API(API/platform specific)**底层硬件交互**

- RenderContext

  渲染上下文,  管理GPU资源（如内存、命令队列）的入口点，所有渲染操作的基础环境。

- Swap chain

  交换链，管理双缓冲/三缓冲机制，实现画面平滑更新的核心组件。

- Framebuffer

  帧缓冲区，存储渲染结果的内存区域（颜色/深度/模板缓冲区）。

- Vertex Buffer

  顶点缓冲区，存储模型顶点坐标、法线等几何数据的GPU内存块。

- Index Buffer

  索引缓冲区，通过索引复用顶点数据，优化复杂模型的存储效率。

- Texture

  纹理，存储图像数据的2D数组，用于表面材质（颜色/法线/粗糙度等）。

- Shader

  着色器，用GLSL/HLSL编写的GPU程序，控制顶点变换、像素着色等。

- States

  渲染状态，如混合模式、深度测试等配置，影响渲染管线行为。

- Pipelines

  渲染管线，定义数据从输入到输出的处理流程（如光栅化→着色→混合）。

- Render passes

  渲染通道，将复杂渲染分解为多个阶段（如先渲染不透明物体，再处理透明物体）。

### Render(API/platform agnostic)**渲染逻辑抽象**

- 2D & 3D Renderer

  - Forward, deferred, etc.

  渲染器，实现具体渲染算法（前向/延迟渲染），处理场景到图像的转换。

- Scene Graph

  场景图，树状结构管理场景对象及其层级关系，优化渲染顺序。

- Sorting

  排序，按材质、深度等对物体排序，减少渲染状态切换开销。

- Culling

  剔除，移除视锥体外/背对相机的物体，提升性能。

- Materials

  材质，定义物体表面属性（如金属度、光泽度）与使用的着色器。  

- LOD

  细节层次，根据距离动态切换低/高细节模型，平衡性能与质量。

- Animation

  动画，处理骨骼蒙皮、顶点变形等动态效果。

- Camera

  相机，定义视口、投影矩阵（透视/正交），控制画面呈现。

- VFX

  视觉特效，增强视觉效果。

- PostFX

  后处理特效，在渲染后应用的效果。

- Other things

  - (eg.reflections, ambient occlusion)

  如屏幕空间反射(SSR)、环境光遮蔽(SSAO)，增强场景真实感