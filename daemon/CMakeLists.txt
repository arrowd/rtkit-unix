add_executable(rtkit-daemon
    main.cpp
)

target_link_libraries(rtkit-daemon PUBLIC RTKitPrivate)

install(TARGETS rtkit-daemon
        RUNTIME DESTINATION libexec
)
