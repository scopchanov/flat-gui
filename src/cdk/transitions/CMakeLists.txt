add_subdirectory(composers)
add_subdirectory(effects)

target_sources(${PROJECT_NAME}
	PRIVATE
	DurationScheme.cpp DurationScheme.h DurationScheme_p.h
	PageCapture.cpp PageCapture.h
	PageTransition.cpp PageTransition.h PageTransition_p.h
	TransitionManager.cpp TransitionManager.h TransitionManager_p.h
	TransitionOptions.h
)
