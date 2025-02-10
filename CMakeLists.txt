cmake_minimum_required(VERSION 3.16)

project(contact_kde VERSION 0.1)


set(QT_MIN_VERSION "6.5.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

# Find necessary packages
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(KPim6Akonadi REQUIRED)
find_package(KF6Contacts REQUIRED)


# Add the executable
add_executable(AlbertAkonadi src/main.cpp)

# Link the necessary libraries
target_link_libraries(AlbertAkonadi KPim6::AkonadiCore KPim6::AkonadiWidgets)
target_link_libraries(AlbertAkonadi KF6::Contacts)

# albert_plugin(
# 				LINK PRIVATE ${KPim6::AkonadiCore KPim6::AkonadiWidgets KF6::Contacts}
# 				QT Widgets
# )
