pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        google()
        mavenCentral()
        // Needed for https://github.com/GrenderG/Toasty (Toast on steroid)
        maven { url = uri("https://www.jitpack.io" ) }
    }
}

rootProject.name = "client"
include(":app")