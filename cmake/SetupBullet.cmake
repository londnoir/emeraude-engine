if ( NOT BULLET_ENABLED )
	message("Enabling Bullet library from local source ...")

	find_package(Bullet REQUIRED)

	target_include_directories(${PROJECT_NAME} PRIVATE ${BULLET_INCLUDE_DIRS})
	target_link_directories(${PROJECT_NAME} PRIVATE ${BULLET_LIBRARIES})

	message("Bullet library enabled !")
	message(" - Headers : ${BULLET_INCLUDE_DIRS}")
	message(" - Libraries : ${BULLET_LIBRARIES}")

	set(BULLET_ENABLED On)
else ()
	message("The Bullet library is already enabled.")
endif ()
