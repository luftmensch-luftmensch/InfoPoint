plugins {
    id("com.android.application")
}

android {
    namespace = "com.infopoint"
    compileSdk = 33

    defaultConfig {
        applicationId = "com.infopoint"
        minSdk = 29
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }

        applicationVariants.all {
            // this method is use to rename your all apk weather
            // it may be signed or unsigned(debug apk)
            this.outputs
                .map { it as com.android.build.gradle.internal.api.BaseVariantOutputImpl }
                .forEach { output ->
                    // val outputFileName = "InfoPoint - ${variant.baseName} - ${variant.versionName} ${variant.versionCode}.apk"
                    output.outputFileName = "InfoPoint.apk"
                }
        }

    }

    buildFeatures {
        // allows binding UI components in layouts to data sources in app using a declarative format rather than programmatically
        dataBinding = true
        viewBinding = true
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_16
        targetCompatibility = JavaVersion.VERSION_16
    }
}

dependencies {
    // In order to fix the annoying bug [Duplicate class kotlin.collections.*] that breaks the buld we are going to define some constraints
    // Taken from https://dev.to/retyui/fix-react-native-android-builds-duplicate-class-kotlincollections-found-in-modules-jetified-kotlin-stdlib-180-2ca7
    constraints {
        implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk7:1.8.0") { because("kotlin-stdlib-jdk7 is now a part of kotlin-stdlib") }
        implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk8:1.8.0") { because("kotlin-stdlib-jdk8 is now a part of kotlin-stdlib") }
    }

    implementation("androidx.appcompat:appcompat:1.6.1")

    // Material Design 3 Pack - https://github.com/material-components/material-components-android
    implementation("com.google.android.material:material:1.9.0")

    // Toast on steroids -> https://github.com/GrenderG/Toasty
    implementation("com.github.GrenderG:Toasty:1.5.2")

    // Splash screen
    implementation("androidx.core:core-splashscreen:1.0.1")
    implementation("com.github.bumptech.glide:glide:4.15.1")

    // Layouts
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    implementation("androidx.recyclerview:recyclerview:1.3.0")

    // Navigation graph
    implementation("androidx.navigation:navigation-fragment:2.6.0")
    implementation("androidx.navigation:navigation-ui:2.6.0")

    // Effects
    implementation("androidx.swiperefreshlayout:swiperefreshlayout:1.1.0")
    implementation("com.facebook.shimmer:shimmer:0.5.0")
    // Eye candy navigation bar
    implementation("com.github.ismaeldivita:chip-navigation-bar:1.4.0")

    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}