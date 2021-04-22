
--  premake vs2019 / premake xcode4

workspace "lua32"
   configurations { "Debug", "Release" }

project "liblua32"
   kind "StaticLib"
   language "C"

   includedirs { "src" }
   files { "../src/*.h", "../src/*.c" }
   excludes { "../src/luac.c", '../src/lua.c'}

   libdirs { "../src" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "lua32"
   kind "ConsoleApp"
   files { "../src/lua.c" }
   links { "liblua32" }

project "luac32"
   kind "ConsoleApp"
   files { "../src/luac.c" }
   links { "liblua32" }