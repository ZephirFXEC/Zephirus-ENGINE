project "GLAD"
    kind "StaticLib"
    language 'C'

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "include/glad/glad.h",
        "include/KHR/khrplateforme.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"