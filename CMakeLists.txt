cmake_minimum_required (VERSION 2.8.6)
project (cppMD)
set (SRC_DIR src )

SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_library(pset 
	${SRC_DIR}/Particle/Particle.cpp
	${SRC_DIR}/Particle/ParticlePool.cpp
	${SRC_DIR}/Particle/ParticleSet.cpp
)

add_library(updator 
	${SRC_DIR}/Simulation/PeriodicBox.cpp
	${SRC_DIR}/ForceField/Lennard-Jones.cpp
	${SRC_DIR}/ForceField/ForceField.cpp
	${SRC_DIR}/Updator/AndersonThermostat.cpp
	${SRC_DIR}/Updator/Nose-Hoover.cpp
	${SRC_DIR}/Updator/VelocityVerlet.cpp
    ${SRC_DIR}/Updator/Metropolis.cpp
)

add_library(estimator
	${SRC_DIR}/Estimator/KineticEnergyEstimator.cpp
	${SRC_DIR}/Estimator/PotentialEstimator.cpp
	${SRC_DIR}/Estimator/MomentumEstimator.cpp
	${SRC_DIR}/Estimator/PairCorrelationEstimator.cpp
	${SRC_DIR}/Estimator/StructureFactorEstimator.cpp
	${SRC_DIR}/Estimator/VelocityCorrelation.cpp
    ${SRC_DIR}/Estimator/VacancyEstimator.cpp
)

add_executable(cppMD
    ${SRC_DIR}/Interface/InputManager.cpp
	${SRC_DIR}/main.cpp
)

target_link_libraries(cppMD pset updator estimator m)
