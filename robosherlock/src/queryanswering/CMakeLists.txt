project(rs_queryanswering)

add_library(rs_queryanswering SHARED
        src/RSQueryActionServer.cpp
        src/ObjectDesignatorFactory.cpp
        src/RosPrologInterface.cpp
        src/SWIPLInterface.cpp
        src/QueryInterface.cpp)
target_link_libraries(rs_queryanswering
        ${rosprolog_LIBRARIES}
        ${SWIPL_LIBRARIES}
        ${catkin_LIBRARIES})

add_library(rs_prologQueries SHARED src/PrologCPPQueries.cpp)
target_link_libraries(rs_prologQueries ${robosherlock_LIBRARIES} 
    ${SWIPL_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(rs_prologQueries ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

rs_add_executable(RSQueryActionClient src/RSQueryActionClient.cpp)
target_link_libraries(RSQueryActionClient rs_queryanswering ${catkin_LIBRARIES})


install(
  TARGETS rs_queryanswering
          rs_prologQueries 
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
) 
