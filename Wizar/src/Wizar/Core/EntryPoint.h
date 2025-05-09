#pragma once

#ifdef WZ_PLATFORM_WINDOWS

extern Wizar::Application* Wizar::CreateApplication();

int main(int argc,char** argv)
{
	Wizar::Log::Init();
	WZ_CORE_WARN("Initialized Log!");
	int a = 5;
	WZ_INFO("welcome! Var={0}", a);
	auto app = Wizar::CreateApplication();
	app->Run();
	delete app;
}

#endif