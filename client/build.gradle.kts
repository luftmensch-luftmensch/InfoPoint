// Top-level build file where you can add configuration options common to all sub-projects/modules.
plugins {
    id("com.android.application") version "8.1.0-beta01" apply false
}

// Show deprecations notice during build
allprojects {
    gradle.projectsEvaluated {

        tasks.withType<JavaCompile> {
            options.compilerArgs.addAll(arrayOf("-parameters", "-Xlint:deprecation"))
        }
    }
}