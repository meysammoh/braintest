# BrainTest - Cross-Platform Memory Game (2015)

A brain training and memory test game built with Cocos2d-x, ported from an original Flash game to C++ for cross-platform mobile and desktop deployment.

<a href="https://www.youtube.com/watch?v=yBhzWbni5t8" target="_blank">
  <img src="https://img.youtube.com/vi/yBhzWbni5t8/0.jpg" alt="Demo Video">
</a>

*Click image to watch demo video*

## Overview

BrainTest is a memory challenge game where players must memorize sequences of numbers displayed briefly on screen, then select them in the correct order. The game adapts difficulty based on performance and calculates a "brain age" score at the end.

**Original Project:** Flash-based web game (2015)
**C++ Port:** July-October 2015
**Platforms:** Android, iOS, Windows, Linux, macOS

## Game Mechanics

- **Objective:** Memorize numbers shown briefly, then click them in ascending order
- **Adaptive Difficulty:**
  - Start with 3 numbers
  - Success increases count (up to 10 numbers)
  - Failure decreases count (minimum 3)
- **10 Rounds:** Complete 10 turns to finish the game
- **Brain Age Calculation:** Performance-based age formula derived from the original Flash version
- **Timer System:** Limited time to memorize numbers before they disappear

## Technical Stack

### Game Engine
- **Cocos2d-x:** Version 3.8 (GitHub commit: `253d9c4d3164f558010add68f4d37a128f1ec95f`)
- **Language:** C++11
- **Build System:** CMake 2.8+

### Target Platforms
- **Android:** Android Studio project included
- **iOS/macOS:** Xcode project (proj.ios_mac)
- **Windows:** Win32, Windows 8.1 Universal, Windows 10 UWP
- **Linux:** Native Linux build

### Resolution Support
Multi-resolution asset system:
- Small (phone portrait)
- Medium (tablet/phone landscape)
- Large (high-resolution displays)

## Project Structure

```
braintest/
├── Classes/              # Game source code (C++)
│   ├── AppDelegate.*     # Application entry point
│   ├── GameScene.*       # Main game screen
│   ├── MainMenuScene.*   # Title screen
│   ├── AboutScene.*      # About/credits screen
│   ├── PauseScene.*      # Pause menu
│   ├── GameManager.*     # Game logic and level management
│   ├── BT_Number.*       # Number display component
│   └── BT_Counter.*      # Timer/counter component
├── Resources/            # Game assets
│   ├── fonts/           # TrueType fonts
│   ├── small/           # Low-res images
│   ├── medium/          # Medium-res images
│   ├── large/           # High-res images
│   └── SoundEffects/    # Audio files
├── Documents/           # Original Flash game reference
│   ├── FlashGameFormule           # Brain age calculation formula
│   ├── FlashGameSourceCode.txt    # Original ActionScript
│   └── IMAG*.jpg                  # Design sketches/photos
├── cocos2d/            # Cocos2d-x engine (v3.8)
├── proj.android/       # Eclipse Android project (deprecated)
├── proj.android-studio/ # Android Studio project
├── proj.ios_mac/       # Xcode project (iOS/Mac)
├── proj.win32/         # Visual Studio Win32 project
├── proj.win10/         # Visual Studio UWP project
├── proj.win8.1-universal/ # Windows 8.1 Universal
├── proj.linux/         # Linux makefile project
└── CMakeLists.txt      # Cross-platform CMake build
```

## Building the Project

### Prerequisites

**All Platforms:**
- CMake 2.8 or higher
- Cocos2d-x 3.8 dependencies (bundled in `cocos2d/` folder)
- C++11 compatible compiler

**Platform-Specific:**
- **Android:** Android SDK, NDK r10+, Android Studio
- **iOS/macOS:** Xcode 7+, macOS 10.10+
- **Windows:** Visual Studio 2013/2015
- **Linux:** GCC 4.9+, OpenGL development libraries

### Build Instructions

#### CMake Build (Linux/Windows/Mac)
```bash
mkdir build
cd build
cmake ..
make
```

#### Android
```bash
cd proj.android-studio
# Import in Android Studio and build
```

#### iOS/macOS
```bash
cd proj.ios_mac
open BrainTest.xcodeproj
# Build in Xcode
```

#### Windows (Visual Studio)
```bash
cd proj.win32
# Open BrainTest.sln in Visual Studio
```

### Running the Game

After building, executables are located in platform-specific output directories:
- **Linux/CMake:** `build/bin/BrainTest`
- **Windows:** `proj.win32/Debug/BrainTest.exe` or `Release/BrainTest.exe`
- **Android:** Install APK on device
- **iOS:** Deploy via Xcode to device/simulator

## Game Features

### Core Gameplay
- **Memory Training:** Progressive difficulty based on player performance
- **Visual Feedback:** Clear number displays with touch/click interaction
- **Sound Effects:** Audio feedback for correct/incorrect selections
- **Score System:** Brain age calculation using performance metrics

### UI Components
- Main menu with play/about options
- Pause menu during gameplay
- Results screen showing brain age
- Share functionality for social features

### Game States
1. **Initializing:** Game setup
2. **Showing Timer:** Countdown before number reveal
3. **Showing Level:** Numbers displayed for memorization
4. **Showing Age:** Brain age calculation display
5. **Waiting for Selection:** Player input phase
6. **Going to Next Level:** Transition between rounds

## Brain Age Algorithm

The game uses a formula derived from the original Flash game:
- Based on total numbers memorized across 10 rounds
- Adjusted by success rate
- Ranges from 20 (excellent) to 120 (needs practice)
- See `Documents/FlashGameFormule` for original algorithm

## Development Notes

### Flash to C++ Port

This project is a faithful port of a Flash-based browser game to native C++ using Cocos2d-x. Key migrations:
- **ActionScript → C++:** Complete rewrite of game logic
- **Flash Timeline → Scene Management:** Cocos2d-x scene system
- **Flash Graphics → Sprites:** Cocos2d-x sprite rendering
- **Formula Preservation:** Brain age calculation maintained from original

### Code Highlights

**GameManager.cpp:**
- Adaptive difficulty algorithm
- Random number generation with spatial distribution
- Grid-based layout system to prevent overlapping numbers

**GameScene.cpp:**
- State machine for game flow
- Touch/keyboard input handling
- Timer and animation management

**BT_Number.cpp:**
- Custom number sprite component
- Click detection and visual feedback
- Integration with game manager

## Assets

### Graphics
- Multi-resolution support (SD/HD/UHD)
- Custom UI elements (buttons, backgrounds)
- Number sprites

### Audio
- Success sound effect
- Failure sound effect
- Background music (if included)

### Fonts
- Custom TrueType fonts for number display
- UI text rendering

## Version History

**2015-10-27:** CMake configuration finalized
**2015-10-02:** Git repository initialized
**2015-08-09:** Flash game formula and source documented
**2015-08-06:** Original Flash source code archived
**2015-08-03:** Design photos/sketches captured
**2015-07-31:** Cocos2d-x 3.8 integration completed
**2015-07-30:** Project created from Flash original

## Cross-Platform Compatibility

Tested and built for:
- ✓ Android 4.1+ (API 16+)
- ✓ iOS 8.0+
- ✓ Windows 7/8/8.1/10
- ✓ macOS 10.10+
- ✓ Linux (Ubuntu 14.04+, various distros)

## Known Dependencies

**Cocos2d-x 3.8 includes:**
- OpenGL ES 2.0 / OpenGL 2.1
- libpng, libjpeg, libwebp (image formats)
- FreeType (font rendering)
- OpenAL / FMOD (audio)
- Box2D / Chipmunk (physics - if used)

All dependencies are bundled in the `cocos2d/` directory - no external installation required.

## Skills Demonstrated

| Category | Skills |
|----------|--------|
| **Cross-Platform Development** | Cocos2d-x, C++11, CMake, multi-platform builds |
| **Mobile Development** | Android NDK, iOS/Xcode, touch input handling |
| **Game Architecture** | Scene management, State machines, Game loop |
| **Code Migration** | Flash/ActionScript to C++ porting |
| **Asset Management** | Multi-resolution sprites, Resource pipelines |
| **Build Systems** | CMake, Android Studio, Visual Studio, Xcode |

## License

MIT License (see LICENSE file)

## Credits

**Development:** 2015
**Original Concept:** Flash web game
**Engine:** Cocos2d-x 3.8
**Port:** Flash ActionScript → C++ native implementation

---

**Note:** This is a preserved project from 2015 showcasing cross-platform mobile game development with Cocos2d-x. The codebase demonstrates:
- Flash-to-native game porting
- Cross-platform C++ development
- Mobile game architecture
- Adaptive difficulty systems
- Multi-resolution asset management
