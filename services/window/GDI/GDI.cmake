if(WIN32)
    OPTION(RADONFRAMEWORK_USE_WINDOW_GDI "Activate window support for GDI" ON)
    mark_as_advanced(RADONFRAMEWORK_USE_WINDOW_GDI)
    
    if(RADONFRAMEWORK_USE_WINDOW_GDI)
        OPTION(RADONFRAMEWORK_STATICLINK_WINDOW_GDI "The GDI window support will be linked into the static lib." OFF)
        mark_as_advanced(RADONFRAMEWORK_STATICLINK_WINDOW_GDI)
    endif()
    
    set(LibTypeGDI "")
    if(RADONFRAMEWORK_STATICLINK_WINDOW_GDI)
        set(LibTypeGDI MODULE)
        rcf_add_internal(RADONFRAMEWORK_STATIC_SERVICE_TARGETS RF_WINDOW_GDI)
        rcf_remove_internal(RADONFRAMEWORK_DYNAMIC_SERVICE_TARGETS WindowGDI)  
    else()
        set(LibTypeGDI SHARED)
        rcf_add_internal(RADONFRAMEWORK_DYNAMIC_SERVICE_TARGETS WindowGDI)
        rcf_remove_internal(RADONFRAMEWORK_STATIC_SERVICE_TARGETS RF_WINDOW_GDI)  
    endif()
    
    AddSourceDirectoryRecursive(filelist "${CMAKE_CURRENT_LIST_DIR}" "Sources")
    list(APPEND RF_WINDOW_GDI_FILES ${filelist})	
    AddHeaderDirectoryRecursive(filelist "${CMAKE_CURRENT_LIST_DIR}" "Includes")
    list(APPEND RF_WINDOW_GDI_FILES ${filelist})		
    if(RADONFRAMEWORK_STATICLINK_WINDOW_GDI)
        list(REMOVE_ITEM RF_WINDOW_GDI_FILES "${CMAKE_CURRENT_LIST_DIR}/Shared.cpp")
    endif()
    Generate(${LibTypeGDI} RF_WINDOW_GDI WindowGDI "Framework")
    AddPublicInclude(RF_WINDOW_GDI "${CMAKE_CURRENT_LIST_DIR}")
    AddDependency(RF_WINDOW_GDI RadonFramework)
    Finalize(RF_WINDOW_GDI)
endif()