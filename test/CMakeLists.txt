cmake_minimum_required(VERSION 2.6)

set(SRC_DIR ../../src)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(particleTest 
	../testParticleSet.cpp
	${SRC_DIR}/Particle/Particle.cpp
	${SRC_DIR}/Particle/ParticleSet.cpp
)

add_executable(boxTest 
	../testPeriodicBox.cpp
	${SRC_DIR}/Particle/Particle.cpp
	${SRC_DIR}/Particle/ParticleSet.cpp
	${SRC_DIR}/Simulation/PeriodicBox.cpp
)

target_link_libraries(particleTest ${GTEST_LIBRARIES} pthread)
target_link_libraries(boxTest ${GTEST_LIBRARIES} pthread m)

