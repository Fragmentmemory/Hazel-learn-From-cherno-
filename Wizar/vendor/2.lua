if os.istarget("windows") then
  toolset "msvc"
elseif os.istarget("linux") then
  toolset "gcc"
end