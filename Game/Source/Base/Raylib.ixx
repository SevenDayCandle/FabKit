export module raylib;

#include "raylib.h"
#include "raymath.h"

export namespace raylib {

	/* Structs */
	export using AudioStream = ::AudioStream;
	export using AutomationEvent = ::AutomationEvent;
	export using AutomationEventList = ::AutomationEventList;
	export using BoneInfo = ::BoneInfo;
	export using BoundingBox = ::BoundingBox;
	export using Camera = ::Camera;
	export using Camera2D = ::Camera2D;
	export using Camera3D = ::Camera3D;
	export using Color = ::Color;
	export using FilePathList = ::FilePathList;
    export using Font = ::Font;
	export using GlyphInfo = ::GlyphInfo;
	export using Image = ::Image;
	export using Material = ::Material;
	export using MaterialMap = ::MaterialMap;
	export using Matrix = ::Matrix;
	export using Mesh = ::Mesh;
	export using Model = ::Model;
	export using ModelAnimation = ::ModelAnimation;
	export using Music = ::Music;
	export using NPatchInfo = ::NPatchInfo;
	export using Ray = ::Ray;
	export using RayCollision = ::RayCollision;
	export using Rectangle = ::Rectangle;
	export using RenderTexture = ::RenderTexture;
	export using Shader = ::Shader;
	export using Sound = ::Sound;
	export using Texture = ::Texture;
	export using Transform = ::Transform;
	export using Vector2 = ::Vector2;
	export using Vector3 = ::Vector3;
	export using Vector4 = ::Vector4;
	export using VrDeviceInfo = ::VrDeviceInfo;
	export using VrStereoConfig = ::VrStereoConfig;
	export using Wave = ::Wave;

    /* Enums */
    export using ConfigFlags = ::ConfigFlags;
    export using KeyboardKey = ::KeyboardKey;
    export using TraceLogLevel = ::TraceLogLevel;
    export using MouseButton = ::MouseButton;
    export using MouseCursor = ::MouseCursor;
    export using GamepadButton = ::GamepadButton;
    export using GamepadAxis = ::GamepadAxis;
    export using MaterialMapIndex = ::MaterialMapIndex;
    export using ShaderLocationIndex = ::ShaderLocationIndex;
    export using ShaderUniformDataType = ::ShaderUniformDataType;
    export using ShaderAttributeDataType = ::ShaderAttributeDataType;
    export using PixelFormat = ::PixelFormat;
    export using TextureFilter = ::TextureFilter;
    export using TextureWrap = ::TextureWrap;
    export using CubemapLayout = ::CubemapLayout;
    export using FontType = ::FontType;
    export using BlendMode = ::BlendMode;
    export using Gesture = ::Gesture;
    export using CameraMode = ::CameraMode;
    export using CameraProjection = ::CameraProjection;
    export using NPatchLayout = ::NPatchLayout;

    /* Constants */
    export constexpr float Pi = PI;
    export constexpr float Deg2Rad = Pi / 180.0f;
    export constexpr float Rad2Deg = 180.0f / Pi;

    export constexpr Color LightGray = ::LIGHTGRAY;
    export constexpr Color Gray = GRAY;
    export constexpr Color DarkGray = DARKGRAY;
    export constexpr Color Yellow = YELLOW;
    export constexpr Color Gold = GOLD;
    export constexpr Color Orange = ORANGE;
    export constexpr Color Pink = PINK;
    export constexpr Color Red = RED;
    export constexpr Color Maroon = MAROON;
    export constexpr Color Green = GREEN;
    export constexpr Color Lime = LIME;
    export constexpr Color DarkGreen = DARKGREEN;
    export constexpr Color SkyBlue = SKYBLUE;
    export constexpr Color Blue = BLUE;
    export constexpr Color DarkBlue = DARKBLUE;
    export constexpr Color Purple = PURPLE;
    export constexpr Color Violet = VIOLET;
    export constexpr Color DarkPurple = DARKPURPLE;
    export constexpr Color Beige = BEIGE;
    export constexpr Color Brown = BROWN;
    export constexpr Color DarkBrown = DARKBROWN;
    export constexpr Color White = WHITE;
    export constexpr Color Black = BLACK;
    export constexpr Color Blank = BLANK;
    export constexpr Color Magenta = MAGENTA;

	/* Functions */

    // Window functions

    export void initWindow(int width, int height, const char* title) { ::InitWindow(width, height, title); }
    export void closeWindow() { ::CloseWindow(); }
    export bool windowShouldClose() { return ::WindowShouldClose(); }
    export bool isWindowReady() { return ::IsWindowReady(); }
    export bool isWindowFullscreen() { return ::IsWindowFullscreen(); }
    export bool isWindowHidden() { return ::IsWindowHidden(); }
    export bool isWindowMinimized() { return ::IsWindowMinimized(); }
    export bool isWindowMaximized() { return ::IsWindowMaximized(); }
    export bool isWindowFocused() { return ::IsWindowFocused(); }
    export bool isWindowResized() { return ::IsWindowResized(); }
    export bool isWindowState(unsigned int flag) { return ::IsWindowState(flag); }
    export void setWindowState(unsigned int flags) { ::SetWindowState(flags); }
    export void clearWindowState(unsigned int flags) { ::ClearWindowState(flags); }
    export void toggleFullscreen() { ::ToggleFullscreen(); }
    export void maximizeWindow() { ::MaximizeWindow(); }
    export void minimizeWindow() { ::MinimizeWindow(); }
    export void restoreWindow() { ::RestoreWindow(); }
    export void setWindowIcon(Image image) { ::SetWindowIcon(image); }
    export void setWindowIcons(Image* images, int count) { ::SetWindowIcons(images, count); }
    export void setWindowTitle(const char* title) { ::SetWindowTitle(title); }
    export void setWindowPosition(int x, int y) { ::SetWindowPosition(x, y); }
    export void setWindowMonitor(int monitor) { ::SetWindowMonitor(monitor); }
    export void setWindowMinSize(int width, int height) { ::SetWindowMinSize(width, height); }
    export void setWindowMaxSize(int width, int height) { ::SetWindowMaxSize(width, height); }
    export void setWindowSize(int width, int height) { ::SetWindowSize(width, height); }
    export void setWindowOpacity(float opacity) { ::SetWindowOpacity(opacity); }
    export void setWindowFocused() { ::SetWindowFocused(); }
    export void* getWindowHandle() { return ::GetWindowHandle(); }
    export int getScreenWidth() { return ::GetScreenWidth(); }
    export int getScreenHeight() { return ::GetScreenHeight(); }
    export int getRenderWidth() { return ::GetRenderWidth(); }
    export int getRenderHeight() { return ::GetRenderHeight(); }
    export int getMonitorCount() { return ::GetMonitorCount(); }
    export int getCurrentMonitor() { return ::GetCurrentMonitor(); }
    export Vector2 getMonitorPosition(int monitor) { return ::GetMonitorPosition(monitor); }
    export int getMonitorWidth(int monitor) { return ::GetMonitorWidth(monitor); }
    export int getMonitorHeight(int monitor) { return ::GetMonitorHeight(monitor); }
    export int getMonitorPhysicalWidth(int monitor) { return ::GetMonitorPhysicalWidth(monitor); }
    export int getMonitorPhysicalHeight(int monitor) { return ::GetMonitorPhysicalHeight(monitor); }
    export int getMonitorRefreshRate(int monitor) { return ::GetMonitorRefreshRate(monitor); }
    export Vector2 getWindowPosition() { return ::GetWindowPosition(); }
    export Vector2 getWindowScaleDPI() { return ::GetWindowScaleDPI(); }
    export const char* getMonitorName(int monitor) { return ::GetMonitorName(monitor); }
    export void setClipboardText(const char* text) { ::SetClipboardText(text); }
    export const char* getClipboardText() { return ::GetClipboardText(); }
    export void enableEventWaiting() { ::EnableEventWaiting(); }
    export void disableEventWaiting() { ::DisableEventWaiting(); }

    // Cursor-related functions
    export void showCursor() { ::ShowCursor(); }
    export void hideCursor() { ::HideCursor(); }
    export bool isCursorHidden() { return ::IsCursorHidden(); }
    export void enableCursor() { ::EnableCursor(); }
    export void disableCursor() { ::DisableCursor(); }
    export bool isCursorOnScreen() { return ::IsCursorOnScreen(); }

    // Drawing-related functions
    export void clearBackground(Color color) { ::ClearBackground(color); }
    export void beginDrawing() { ::BeginDrawing(); }
    export void endDrawing() { ::EndDrawing(); }
    export void beginMode2D(Camera2D camera) { ::BeginMode2D(camera); }
    export void endMode2D() { ::EndMode2D(); }
    export void beginMode3D(Camera3D camera) { ::BeginMode3D(camera); }
    export void endMode3D() { ::EndMode3D(); }
    export void beginTextureMode(RenderTexture2D target) { ::BeginTextureMode(target); }
    export void endTextureMode() { ::EndTextureMode(); }
    export void beginShaderMode(Shader shader) { ::BeginShaderMode(shader); }
    export void endShaderMode() { ::EndShaderMode(); }
    export void beginBlendMode(int mode) { ::BeginBlendMode(mode); }
    export void endBlendMode() { ::EndBlendMode(); }
    export void beginScissorMode(int x, int y, int width, int height) { ::BeginScissorMode(x, y, width, height); }
    export void endScissorMode() { ::EndScissorMode(); }
    export void beginVrStereoMode(VrStereoConfig config) { ::BeginVrStereoMode(config); }
    export void endVrStereoMode() { ::EndVrStereoMode(); }

    // VR stereo config functions for VR simulator
    export VrStereoConfig loadVrStereoConfig(VrDeviceInfo device) { return ::LoadVrStereoConfig(device); }
    export void unloadVrStereoConfig(VrStereoConfig config) { ::UnloadVrStereoConfig(config); }

    // Shader management functions
    export Shader loadShader(const char* vsFileName, const char* fsFileName) { return ::LoadShader(vsFileName, fsFileName); }
    export Shader loadShaderFromMemory(const char* vsCode, const char* fsCode) { return ::LoadShaderFromMemory(vsCode, fsCode); }
    export bool isShaderReady(Shader shader) { return ::IsShaderReady(shader); }
    export int getShaderLocation(Shader shader, const char* uniformName) { return ::GetShaderLocation(shader, uniformName); }
    export int getShaderLocationAttrib(Shader shader, const char* attribName) { return ::GetShaderLocationAttrib(shader, attribName); }
    export void setShaderValue(Shader shader, int locIndex, const void* value, int uniformType) { ::SetShaderValue(shader, locIndex, value, uniformType); }
    export void setShaderValueV(Shader shader, int locIndex, const void* value, int uniformType, int count) { ::SetShaderValueV(shader, locIndex, value, uniformType, count); }
    export void setShaderValueMatrix(Shader shader, int locIndex, Matrix mat) { ::SetShaderValueMatrix(shader, locIndex, mat); }
    export void setShaderValueTexture(Shader shader, int locIndex, Texture2D texture) { ::SetShaderValueTexture(shader, locIndex, texture); }
    export void unloadShader(Shader shader) { ::UnloadShader(shader); }

    // Timing-related functions
    export void setTargetFPS(int fps) { ::SetTargetFPS(fps); }
    export float getFrameTime() { return ::GetFrameTime(); }
    export double getTime() { return ::GetTime(); }
    export int getFPS() { return ::GetFPS(); }

    // Custom frame control functions
    export void swapScreenBuffer() { ::SwapScreenBuffer(); }
    export void pollInputEvents() { ::PollInputEvents(); }
    export void waitTime(double seconds) { ::WaitTime(seconds); }

    // Random values generation functions
    export void setRandomSeed(unsigned int seed) { ::SetRandomSeed(seed); }
    export int getRandomValue(int min, int max) { return ::GetRandomValue(min, max); }
    export int* loadRandomSequence(unsigned int count, int min, int max) { return ::LoadRandomSequence(count, min, max); }
    export void unloadRandomSequence(int* sequence) { ::UnloadRandomSequence(sequence); }

    // Misc. functions
    export void takeScreenshot(const char* fileName) { ::TakeScreenshot(fileName); }
    export void setConfigFlags(unsigned int flags) { ::SetConfigFlags(flags); }
    export void openURL(const char* url) { ::OpenURL(url); }
    export void traceLog(int logLevel, const char* text, ...) { ::TraceLog(logLevel, text); }
    export void setTraceLogLevel(int logLevel) { ::SetTraceLogLevel(logLevel); }
    export void* memAlloc(unsigned int size) { return ::MemAlloc(size); }
    export void* memRealloc(void* ptr, unsigned int size) { return ::MemRealloc(ptr, size); }
    export void memFree(void* ptr) { ::MemFree(ptr); }

    // Set custom callbacks
    export void setTraceLogCallback(TraceLogCallback callback) { ::SetTraceLogCallback(callback); }
    export void setLoadFileDataCallback(LoadFileDataCallback callback) { ::SetLoadFileDataCallback(callback); }
    export void setSaveFileDataCallback(SaveFileDataCallback callback) { ::SetSaveFileDataCallback(callback); }
    export void setLoadFileTextCallback(LoadFileTextCallback callback) { ::SetLoadFileTextCallback(callback); }
    export void setSaveFileTextCallback(SaveFileTextCallback callback) { ::SetSaveFileTextCallback(callback); }

    // Files management functions
    export unsigned char* loadFileData(const char* fileName, int* dataSize) { return ::LoadFileData(fileName, dataSize); }
    export void unloadFileData(unsigned char* data) { ::UnloadFileData(data); }
    export bool saveFileData(const char* fileName, void* data, int dataSize) { return ::SaveFileData(fileName, data, dataSize); }
    export bool exportDataAsCode(const unsigned char* data, int dataSize, const char* fileName) { return ::ExportDataAsCode(data, dataSize, fileName); }
    export char* loadFileText(const char* fileName) { return ::LoadFileText(fileName); }
    export void unloadFileText(char* text) { ::UnloadFileText(text); }
    export bool saveFileText(const char* fileName, char* text) { return ::SaveFileText(fileName, text); }

    // File system functions
    export bool fileExists(const char* fileName) { return ::FileExists(fileName); }
    export bool directoryExists(const char* dirPath) { return ::DirectoryExists(dirPath); }
    export bool isFileExtension(const char* fileName, const char* ext) { return ::IsFileExtension(fileName, ext); }
    export int getFileLength(const char* fileName) { return ::GetFileLength(fileName); }
    export const char* getFileExtension(const char* fileName) { return ::GetFileExtension(fileName); }
    export const char* getFileName(const char* filePath) { return ::GetFileName(filePath); }
    export const char* getFileNameWithoutExt(const char* filePath) { return ::GetFileNameWithoutExt(filePath); }
    export const char* getDirectoryPath(const char* filePath) { return ::GetDirectoryPath(filePath); }
    export const char* getPrevDirectoryPath(const char* dirPath) { return ::GetPrevDirectoryPath(dirPath); }
    export const char* getWorkingDirectory() { return ::GetWorkingDirectory(); }
    export const char* getApplicationDirectory() { return ::GetApplicationDirectory(); }
    export bool changeDirectory(const char* dir) { return ::ChangeDirectory(dir); }
    export bool isPathFile(const char* path) { return ::IsPathFile(path); }
    export FilePathList loadDirectoryFiles(const char* dirPath) { return ::LoadDirectoryFiles(dirPath); }
    export FilePathList loadDirectoryFilesEx(const char* basePath, const char* filter, bool scanSubdirs) { return ::LoadDirectoryFilesEx(basePath, filter, scanSubdirs); }
    export void unloadDirectoryFiles(FilePathList files) { ::UnloadDirectoryFiles(files); }
    export bool isFileDropped() { return ::IsFileDropped(); }
    export FilePathList loadDroppedFiles() { return ::LoadDroppedFiles(); }
    export void unloadDroppedFiles(FilePathList files) { ::UnloadDroppedFiles(files); }
    export long getFileModTime(const char* fileName) { return ::GetFileModTime(fileName); }

    // Compression/Encoding functionality
    export unsigned char* compressData(const unsigned char* data, int dataSize, int* compDataSize) { return ::CompressData(data, dataSize, compDataSize); }
    export unsigned char* decompressData(const unsigned char* compData, int compDataSize, int* dataSize) { return ::DecompressData(compData, compDataSize, dataSize); }
    export char* encodeDataBase64(const unsigned char* data, int dataSize, int* outputSize) { return ::EncodeDataBase64(data, dataSize, outputSize); }
    export unsigned char* decodeDataBase64(const unsigned char* data, int* outputSize) { return ::DecodeDataBase64(data, outputSize); }

    // Automation events functionality
    export AutomationEventList loadAutomationEventList(const char* fileName) { return ::LoadAutomationEventList(fileName); }
    export void unloadAutomationEventList(AutomationEventList* list) { ::UnloadAutomationEventList(list); }
    export bool exportAutomationEventList(AutomationEventList list, const char* fileName) { return ::ExportAutomationEventList(list, fileName); }
    export void setAutomationEventList(AutomationEventList* list) { ::SetAutomationEventList(list); }
    export void setAutomationEventBaseFrame(int frame) { ::SetAutomationEventBaseFrame(frame); }
    export void startAutomationEventRecording() { ::StartAutomationEventRecording(); }
    export void stopAutomationEventRecording() { ::StopAutomationEventRecording(); }
    export void playAutomationEvent(AutomationEvent event) { ::PlayAutomationEvent(event); }

    // Input-related functions: keyboard
    export bool isKeyPressed(int key) { return ::IsKeyPressed(key); }
    export bool isKeyPressedRepeat(int key) { return ::IsKeyPressedRepeat(key); }
    export bool isKeyDown(int key) { return ::IsKeyDown(key); }
    export bool isKeyReleased(int key) { return ::IsKeyReleased(key); }
    export bool isKeyUp(int key) { return ::IsKeyUp(key); }
    export int getKeyPressed() { return ::GetKeyPressed(); }
    export int getCharPressed() { return ::GetCharPressed(); }
    export void setExitKey(int key) { ::SetExitKey(key); }

    // Input-related functions: gamepads
    export bool isGamepadAvailable(int gamepad) { return ::IsGamepadAvailable(gamepad); }
    export const char* getGamepadName(int gamepad) { return ::GetGamepadName(gamepad); }
    export bool isGamepadButtonPressed(int gamepad, int button) { return ::IsGamepadButtonPressed(gamepad, button); }
    export bool isGamepadButtonDown(int gamepad, int button) { return ::IsGamepadButtonDown(gamepad, button); }
    export bool isGamepadButtonReleased(int gamepad, int button) { return ::IsGamepadButtonReleased(gamepad, button); }
    export bool isGamepadButtonUp(int gamepad, int button) { return ::IsGamepadButtonUp(gamepad, button); }
    export int getGamepadButtonPressed() { return ::GetGamepadButtonPressed(); }
    export int getGamepadAxisCount(int gamepad) { return ::GetGamepadAxisCount(gamepad); }
    export float getGamepadAxisMovement(int gamepad, int axis) { return ::GetGamepadAxisMovement(gamepad, axis); }
    export int setGamepadMappings(const char* mappings) { return ::SetGamepadMappings(mappings); }

    // Input-related functions: mouse
    export bool isMouseButtonPressed(int button) { return ::IsMouseButtonPressed(button); }
    export bool isMouseButtonDown(int button) { return ::IsMouseButtonDown(button); }
    export bool isMouseButtonReleased(int button) { return ::IsMouseButtonReleased(button); }
    export bool isMouseButtonUp(int button) { return ::IsMouseButtonUp(button); }
    export int getMouseX() { return ::GetMouseX(); }
    export int getMouseY() { return ::GetMouseY(); }
    export Vector2 getMousePosition() { return ::GetMousePosition(); }
    export Vector2 getMouseDelta() { return ::GetMouseDelta(); }
    export void setMousePosition(int x, int y) { ::SetMousePosition(x, y); }
    export void setMouseOffset(int offsetX, int offsetY) { ::SetMouseOffset(offsetX, offsetY); }
    export void setMouseScale(float scaleX, float scaleY) { ::SetMouseScale(scaleX, scaleY); }
    export float getMouseWheelMove() { return ::GetMouseWheelMove(); }
    export Vector2 getMouseWheelMoveV() { return ::GetMouseWheelMoveV(); }
    export void setMouseCursor(int cursor) { ::SetMouseCursor(cursor); }

    // Input-related functions: touch
    export int getTouchX() { return ::GetTouchX(); }
    export int getTouchY() { return ::GetTouchY(); }
    export Vector2 getTouchPosition(int index) { return ::GetTouchPosition(index); }
    export int getTouchPointId(int index) { return ::GetTouchPointId(index); }
    export int getTouchPointCount() { return ::GetTouchPointCount(); }
    export void setGesturesEnabled(unsigned int flags) { ::SetGesturesEnabled(flags); }
    export bool isGestureDetected(unsigned int gesture) { return ::IsGestureDetected(gesture); }
    export int getGestureDetected() { return ::GetGestureDetected(); }
    export float getGestureHoldDuration() { return ::GetGestureHoldDuration(); }
    export Vector2 getGestureDragVector() { return ::GetGestureDragVector(); }
    export float getGestureDragAngle() { return ::GetGestureDragAngle(); }
    export Vector2 getGesturePinchVector() { return ::GetGesturePinchVector(); }
    export float getGesturePinchAngle() { return ::GetGesturePinchAngle(); }

    // Camera
    export void updateCamera(Camera* camera, int mode) { ::UpdateCamera(camera, mode); }
    export void updateCameraPro(Camera* camera, Vector3 movement, Vector3 rotation, float zoom) { ::UpdateCameraPro(camera, movement, rotation, zoom); }

    // Shape drawing
    export void drawPixel(int posX, int posY, Color color) { ::DrawPixel(posX, posY, color); }
    export void drawPixelV(Vector2 position, Color color) { ::DrawPixelV(position, color); }
    export void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) { ::DrawLine(startPosX, startPosY, endPosX, endPosY, color); }
    export void drawLineV(Vector2 startPos, Vector2 endPos, Color color) { ::DrawLineV(startPos, endPos, color); }
    export void drawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color) { ::DrawLineEx(startPos, endPos, thick, color); }
    export void drawLineStrip(Vector2* points, int pointCount, Color color) { ::DrawLineStrip(points, pointCount, color); }
    export void drawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color) { ::DrawLineBezier(startPos, endPos, thick, color); }
    export void drawCircle(int centerX, int centerY, float radius, Color color) { ::DrawCircle(centerX, centerY, radius, color); }
    export void drawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) { ::DrawCircleSector(center, radius, startAngle, endAngle, segments, color); }
    export void drawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) { ::DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color); }
    export void drawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2) { ::DrawCircleGradient(centerX, centerY, radius, color1, color2); }
    export void drawCircleV(Vector2 center, float radius, Color color) { ::DrawCircleV(center, radius, color); }
    export void drawCircleLines(int centerX, int centerY, float radius, Color color) { ::DrawCircleLines(centerX, centerY, radius, color); }
    export void drawCircleLinesV(Vector2 center, float radius, Color color) { ::DrawCircleLinesV(center, radius, color); }
    export void drawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color) { ::DrawEllipse(centerX, centerY, radiusH, radiusV, color); }
    export void drawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color) { ::DrawEllipseLines(centerX, centerY, radiusH, radiusV, color); }
    export void drawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) { ::DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color); }
    export void drawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) { ::DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color); }
    export void drawRectangle(int posX, int posY, int width, int height, Color color) { ::DrawRectangle(posX, posY, width, height, color); }
    export void drawRectangleV(Vector2 position, Vector2 size, Color color) { ::DrawRectangleV(position, size, color); }
    export void drawRectangleRec(Rectangle rec, Color color) { ::DrawRectangleRec(rec, color); }
    export void drawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color) { ::DrawRectanglePro(rec, origin, rotation, color); }
    export void drawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2) { ::DrawRectangleGradientV(posX, posY, width, height, color1, color2); }
    export void drawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2) { ::DrawRectangleGradientH(posX, posY, width, height, color1, color2); }
    export void drawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4) { ::DrawRectangleGradientEx(rec, col1, col2, col3, col4); }
    export void drawRectangleLines(int posX, int posY, int width, int height, Color color) { ::DrawRectangleLines(posX, posY, width, height, color); }
    export void drawRectangleLinesEx(Rectangle rec, float lineThick, Color color) { ::DrawRectangleLinesEx(rec, lineThick, color); }
    export void drawRectangleRounded(Rectangle rec, float roundness, int segments, Color color) { ::DrawRectangleRounded(rec, roundness, segments, color); }
    export void drawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color) { ::DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color); }
    export void drawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) { ::DrawTriangle(v1, v2, v3, color); }
    export void drawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color) { ::DrawTriangleLines(v1, v2, v3, color); }
    export void drawTriangleFan(Vector2* points, int pointCount, Color color) { ::DrawTriangleFan(points, pointCount, color); }
    export void drawTriangleStrip(Vector2* points, int pointCount, Color color) { ::DrawTriangleStrip(points, pointCount, color); }
    export void drawPoly(Vector2 center, int sides, float radius, float rotation, Color color) { ::DrawPoly(center, sides, radius, rotation, color); }
    export void drawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color) { ::DrawPolyLines(center, sides, radius, rotation, color); }
    export void drawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color) { ::DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color); }

    // Splines drawing functions
    export void drawSplineLinear(Vector2* points, int pointCount, float thick, Color color) { ::DrawSplineLinear(points, pointCount, thick, color); }
    export void drawSplineBasis(Vector2* points, int pointCount, float thick, Color color) { ::DrawSplineBasis(points, pointCount, thick, color); }
    export void drawSplineCatmullRom(Vector2* points, int pointCount, float thick, Color color) { ::DrawSplineCatmullRom(points, pointCount, thick, color); }
    export void drawSplineBezierQuadratic(Vector2* points, int pointCount, float thick, Color color) { ::DrawSplineBezierQuadratic(points, pointCount, thick, color); }
    export void drawSplineBezierCubic(Vector2* points, int pointCount, float thick, Color color) { ::DrawSplineBezierCubic(points, pointCount, thick, color); }
    export void drawSplineSegmentLinear(Vector2 p1, Vector2 p2, float thick, Color color) { ::DrawSplineSegmentLinear(p1, p2, thick, color); }
    export void drawSplineSegmentBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color) { ::DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color); }
    export void drawSplineSegmentCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color) { ::DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color); }
    export void drawSplineSegmentBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color) { ::DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color); }
    export void drawSplineSegmentBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color) { ::DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color); }
    export Vector2 getSplinePointLinear(Vector2 startPos, Vector2 endPos, float t) { return ::GetSplinePointLinear(startPos, endPos, t); }
    export Vector2 getSplinePointBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t) { return ::GetSplinePointBasis(p1, p2, p3, p4, t); }
    export Vector2 getSplinePointCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t) { return ::GetSplinePointCatmullRom(p1, p2, p3, p4, t); }
    export Vector2 getSplinePointBezierQuad(Vector2 p1, Vector2 c2, Vector2 p3, float t) { return ::GetSplinePointBezierQuad(p1, c2, p3, t); }
    export Vector2 getSplinePointBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t) { return ::GetSplinePointBezierCubic(p1, c2, c3, p4, t); }

    // Basic shapes collision detection functions
    export bool checkCollisionRecs(Rectangle rec1, Rectangle rec2) { return ::CheckCollisionRecs(rec1, rec2); }
    export bool checkCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2) { return ::CheckCollisionCircles(center1, radius1, center2, radius2); }
    export bool checkCollisionCircleRec(Vector2 center, float radius, Rectangle rec) { return ::CheckCollisionCircleRec(center, radius, rec); }
    export bool checkCollisionPointRec(Vector2 point, Rectangle rec) { return ::CheckCollisionPointRec(point, rec); }
    export bool checkCollisionPointCircle(Vector2 point, Vector2 center, float radius) { return ::CheckCollisionPointCircle(point, center, radius); }
    export bool checkCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3) { return ::CheckCollisionPointTriangle(point, p1, p2, p3); }
    export bool checkCollisionPointPoly(Vector2 point, Vector2* points, int pointCount) { return ::CheckCollisionPointPoly(point, points, pointCount); }
    export bool checkCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2* collisionPoint) { return ::CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, collisionPoint); }
    export bool checkCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold) { return ::CheckCollisionPointLine(point, p1, p2, threshold); }
    export Rectangle getCollisionRec(Rectangle rec1, Rectangle rec2) { return ::GetCollisionRec(rec1, rec2); }

    // Image loading functions
    export Image loadImage(const char* fileName) { return ::LoadImage(fileName); }
    export Image loadImageRaw(const char* fileName, int width, int height, int format, int headerSize) { return ::LoadImageRaw(fileName, width, height, format, headerSize); }
    export Image loadImageSvg(const char* fileNameOrString, int width, int height) { return ::LoadImageSvg(fileNameOrString, width, height); }
    export Image loadImageAnim(const char* fileName, int* frames) { return ::LoadImageAnim(fileName, frames); }
    export Image loadImageFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) { return ::LoadImageFromMemory(fileType, fileData, dataSize); }
    export Image loadImageFromTexture(Texture2D texture) { return ::LoadImageFromTexture(texture); }
    export Image loadImageFromScreen() { return ::LoadImageFromScreen(); }
    export bool isImageReady(Image image) { return ::IsImageReady(image); }
    export void unloadImage(Image image) { ::UnloadImage(image); }
    export bool exportImage(Image image, const char* fileName) { return ::ExportImage(image, fileName); }
    export unsigned char* exportImageToMemory(Image image, const char* fileType, int* fileSize) { return ::ExportImageToMemory(image, fileType, fileSize); }
    export bool exportImageAsCode(Image image, const char* fileName) { return ::ExportImageAsCode(image, fileName); }

    // Image generation functions
    export Image genImageColor(int width, int height, Color color) { return ::GenImageColor(width, height, color); }
    export Image genImageGradientLinear(int width, int height, int direction, Color start, Color end) { return ::GenImageGradientLinear(width, height, direction, start, end); }
    export Image genImageGradientRadial(int width, int height, float density, Color inner, Color outer) { return ::GenImageGradientRadial(width, height, density, inner, outer); }
    export Image genImageGradientSquare(int width, int height, float density, Color inner, Color outer) { return ::GenImageGradientSquare(width, height, density, inner, outer); }
    export Image genImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2) { return ::GenImageChecked(width, height, checksX, checksY, col1, col2); }
    export Image genImageWhiteNoise(int width, int height, float factor) { return ::GenImageWhiteNoise(width, height, factor); }
    export Image genImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale) { return ::GenImagePerlinNoise(width, height, offsetX, offsetY, scale); }
    export Image genImageCellular(int width, int height, int tileSize) { return ::GenImageCellular(width, height, tileSize); }
    export Image genImageText(int width, int height, const char* text) { return ::GenImageText(width, height, text); }

    // Image manipulation functions
    export Image imageCopy(Image image) { return ::ImageCopy(image); }
    export Image imageFromImage(Image image, Rectangle rec) { return ::ImageFromImage(image, rec); }
    export Image imageText(const char* text, int fontSize, Color color) { return ::ImageText(text, fontSize, color); }
    export Image imageTextEx(Font font, const char* text, float fontSize, float spacing, Color tint) { return ::ImageTextEx(font, text, fontSize, spacing, tint); }
    export void imageFormat(Image* image, int newFormat) { ::ImageFormat(image, newFormat); }
    export void imageToPOT(Image* image, Color fill) { ::ImageToPOT(image, fill); }
    export void imageCrop(Image* image, Rectangle crop) { ::ImageCrop(image, crop); }
    export void imageAlphaCrop(Image* image, float threshold) { ::ImageAlphaCrop(image, threshold); }
    export void imageAlphaClear(Image* image, Color color, float threshold) { ::ImageAlphaClear(image, color, threshold); }
    export void imageAlphaMask(Image* image, Image alphaMask) { ::ImageAlphaMask(image, alphaMask); }
    export void imageAlphaPremultiply(Image* image) { ::ImageAlphaPremultiply(image); }
    export void imageBlurGaussian(Image* image, int blurSize) { ::ImageBlurGaussian(image, blurSize); }
    export void imageResize(Image* image, int newWidth, int newHeight) { ::ImageResize(image, newWidth, newHeight); }
    export void imageResizeNN(Image* image, int newWidth, int newHeight) { ::ImageResizeNN(image, newWidth, newHeight); }
    export void imageResizeCanvas(Image* image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill) { ::ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill); }
    export void imageMipmaps(Image* image) { ::ImageMipmaps(image); }
    export void imageDither(Image* image, int rBpp, int gBpp, int bBpp, int aBpp) { ::ImageDither(image, rBpp, gBpp, bBpp, aBpp); }
    export void imageFlipVertical(Image* image) { ::ImageFlipVertical(image); }
    export void imageFlipHorizontal(Image* image) { ::ImageFlipHorizontal(image); }
    export void imageRotate(Image* image, int degrees) { ::ImageRotate(image, degrees); }
    export void imageRotateCW(Image* image) { ::ImageRotateCW(image); }
    export void imageRotateCCW(Image* image) { ::ImageRotateCCW(image); }
    export void imageColorTint(Image* image, Color color) { ::ImageColorTint(image, color); }
    export void imageColorInvert(Image* image) { ::ImageColorInvert(image); }
    export void imageColorGrayscale(Image* image) { ::ImageColorGrayscale(image); }
    export void imageColorContrast(Image* image, float contrast) { ::ImageColorContrast(image, contrast); }
    export void imageColorBrightness(Image* image, int brightness) { ::ImageColorBrightness(image, brightness); }
    export void imageColorReplace(Image* image, Color color, Color replace) { ::ImageColorReplace(image, color, replace); }
    export Color* loadImageColors(Image image) { return ::LoadImageColors(image); }
    export Color* loadImagePalette(Image image, int maxPaletteSize, int* colorCount) { return ::LoadImagePalette(image, maxPaletteSize, colorCount); }
    export void unloadImageColors(Color* colors) { ::UnloadImageColors(colors); }
    export void unloadImagePalette(Color* colors) { ::UnloadImagePalette(colors); }
    export Rectangle getImageAlphaBorder(Image image, float threshold) { return ::GetImageAlphaBorder(image, threshold); }
    export Color getImageColor(Image image, int x, int y) { return ::GetImageColor(image, x, y); }

    // Image drawing functions
    export void imageClearBackground(Image* dst, Color color) { ::ImageClearBackground(dst, color); }
    export void imageDrawPixel(Image* dst, int posX, int posY, Color color) { ::ImageDrawPixel(dst, posX, posY, color); }
    export void imageDrawPixelV(Image* dst, Vector2 position, Color color) { ::ImageDrawPixelV(dst, position, color); }
    export void imageDrawLine(Image* dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color) { ::ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color); }
    export void imageDrawLineV(Image* dst, Vector2 start, Vector2 end, Color color) { ::ImageDrawLineV(dst, start, end, color); }
    export void imageDrawCircle(Image* dst, int centerX, int centerY, int radius, Color color) { ::ImageDrawCircle(dst, centerX, centerY, radius, color); }
    export void imageDrawCircleV(Image* dst, Vector2 center, int radius, Color color) { ::ImageDrawCircleV(dst, center, radius, color); }
    export void imageDrawCircleLines(Image* dst, int centerX, int centerY, int radius, Color color) { ::ImageDrawCircleLines(dst, centerX, centerY, radius, color); }
    export void imageDrawCircleLinesV(Image* dst, Vector2 center, int radius, Color color) { ::ImageDrawCircleLinesV(dst, center, radius, color); }
    export void imageDrawRectangle(Image* dst, int posX, int posY, int width, int height, Color color) { ::ImageDrawRectangle(dst, posX, posY, width, height, color); }
    export void imageDrawRectangleV(Image* dst, Vector2 position, Vector2 size, Color color) { ::ImageDrawRectangleV(dst, position, size, color); }
    export void imageDrawRectangleRec(Image* dst, Rectangle rec, Color color) { ::ImageDrawRectangleRec(dst, rec, color); }
    export void imageDrawRectangleLines(Image* dst, Rectangle rec, int thick, Color color) { ::ImageDrawRectangleLines(dst, rec, thick, color); }
    export void imageDraw(Image* dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint) { ::ImageDraw(dst, src, srcRec, dstRec, tint); }
    export void imageDrawText(Image* dst, const char* text, int posX, int posY, int fontSize, Color color) { ::ImageDrawText(dst, text, posX, posY, fontSize, color); }
    export void imageDrawTextEx(Image* dst, Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint) { ::ImageDrawTextEx(dst, font, text, position, fontSize, spacing, tint); }

    // Texture loading functions
    export Texture2D loadTexture(const char* fileName) { return ::LoadTexture(fileName); }
    export Texture2D loadTextureFromImage(Image image) { return ::LoadTextureFromImage(image); }
    export TextureCubemap loadTextureCubemap(Image image, int layout) { return ::LoadTextureCubemap(image, layout); }
    export RenderTexture2D loadRenderTexture(int width, int height) { return ::LoadRenderTexture(width, height); }
    export bool isTextureReady(Texture2D texture) { return ::IsTextureReady(texture); }
    export void unloadTexture(Texture2D texture) { ::UnloadTexture(texture); }
    export bool isRenderTextureReady(RenderTexture2D target) { return ::IsRenderTextureReady(target); }
    export void unloadRenderTexture(RenderTexture2D target) { ::UnloadRenderTexture(target); }
    export void updateTexture(Texture2D texture, const void* pixels) { ::UpdateTexture(texture, pixels); }
    export void updateTextureRec(Texture2D texture, Rectangle rec, const void* pixels) { ::UpdateTextureRec(texture, rec, pixels); }

    // Texture configuration functions
    export void genTextureMipmaps(Texture2D* texture) { ::GenTextureMipmaps(texture); }
    export void setTextureFilter(Texture2D texture, int filter) { ::SetTextureFilter(texture, filter); }
    export void setTextureWrap(Texture2D texture, int wrap) { ::SetTextureWrap(texture, wrap); }

    // Texture drawing functions
    export void drawTexture(Texture2D texture, int posX, int posY, Color tint) { ::DrawTexture(texture, posX, posY, tint); }
    export void drawTextureV(Texture2D texture, Vector2 position, Color tint) { ::DrawTextureV(texture, position, tint); }
    export void drawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint) { ::DrawTextureEx(texture, position, rotation, scale, tint); }
    export void drawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint) { ::DrawTextureRec(texture, source, position, tint); }
    export void drawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) { ::DrawTexturePro(texture, source, dest, origin, rotation, tint); }
    export void drawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint) { ::DrawTextureNPatch(texture, nPatchInfo, dest, origin, rotation, tint); }

    // Color/pixel related functions
    export Color fade(Color color, float alpha) { return ::Fade(color, alpha); }
    export int colorToInt(Color color) { return ::ColorToInt(color); }
    export Vector4 colorNormalize(Color color) { return ::ColorNormalize(color); }
    export Color colorFromNormalized(Vector4 normalized) { return ::ColorFromNormalized(normalized); }
    export Vector3 colorToHSV(Color color) { return ::ColorToHSV(color); }
    export Color colorFromHSV(float hue, float saturation, float value) { return ::ColorFromHSV(hue, saturation, value); }
    export Color colorTint(Color color, Color tint) { return ::ColorTint(color, tint); }
    export Color colorBrightness(Color color, float factor) { return ::ColorBrightness(color, factor); }
    export Color colorContrast(Color color, float contrast) { return ::ColorContrast(color, contrast); }
    export Color colorAlpha(Color color, float alpha) { return ::ColorAlpha(color, alpha); }
    export Color colorAlphaBlend(Color dst, Color src, Color tint) { return ::ColorAlphaBlend(dst, src, tint); }
    export Color getColor(unsigned int hexValue) { return ::GetColor(hexValue); }
    export Color getPixelColor(void* srcPtr, int format) { return ::GetPixelColor(srcPtr, format); }
    export void setPixelColor(void* dstPtr, Color color, int format) { ::SetPixelColor(dstPtr, color, format); }
    export int getPixelDataSize(int width, int height, int format) { return ::GetPixelDataSize(width, height, format); }

    // Font loading/unloading functions
    export Font getFontDefault() { return ::GetFontDefault(); }
    export Font loadFont(const char* fileName) { return ::LoadFont(fileName); }
    export Font loadFontEx(const char* fileName, int fontSize, int* codepoints, int codepointCount) { return ::LoadFontEx(fileName, fontSize, codepoints, codepointCount); }
    export Font loadFontFromImage(Image image, Color key, int firstChar) { return ::LoadFontFromImage(image, key, firstChar); }
    export Font loadFontFromMemory(const char* fileType, const unsigned char* fileData, int dataSize, int fontSize, int* codepoints, int codepointCount) { return ::LoadFontFromMemory(fileType, fileData, dataSize, fontSize, codepoints, codepointCount); }
    export bool isFontReady(Font font) { return ::IsFontReady(font); }
    export GlyphInfo* loadFontData(const unsigned char* fileData, int dataSize, int fontSize, int* codepoints, int codepointCount, int type) { return ::LoadFontData(fileData, dataSize, fontSize, codepoints, codepointCount, type); }
    export Image genImageFontAtlas(const GlyphInfo* glyphs, Rectangle** glyphRecs, int glyphCount, int fontSize, int padding, int packMethod) { return ::GenImageFontAtlas(glyphs, glyphRecs, glyphCount, fontSize, padding, packMethod); }
    export void unloadFontData(GlyphInfo* glyphs, int glyphCount) { ::UnloadFontData(glyphs, glyphCount); }
    export void unloadFont(Font font) { ::UnloadFont(font); }
    export bool exportFontAsCode(Font font, const char* fileName) { return ::ExportFontAsCode(font, fileName); }

    // Text drawing functions
    export void drawFPS(int posX, int posY) { ::DrawFPS(posX, posY); }
    export void drawText(const char* text, int posX, int posY, int fontSize, Color color) { ::DrawText(text, posX, posY, fontSize, color); }
    export void drawTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint) { ::DrawTextEx(font, text, position, fontSize, spacing, tint); }
    export void drawTextPro(Font font, const char* text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint) { ::DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint); }
    export void drawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint) { ::DrawTextCodepoint(font, codepoint, position, fontSize, tint); }
    export void drawTextCodepoints(Font font, const int* codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint) { ::DrawTextCodepoints(font, codepoints, codepointCount, position, fontSize, spacing, tint); }

    // Text font info functions
    export void setTextLineSpacing(int spacing) { ::SetTextLineSpacing(spacing); }
    export int measureText(const char* text, int fontSize) { return ::MeasureText(text, fontSize); }
    export Vector2 measureTextEx(Font font, const char* text, float fontSize, float spacing) { return ::MeasureTextEx(font, text, fontSize, spacing); }
    export int getGlyphIndex(Font font, int codepoint) { return ::GetGlyphIndex(font, codepoint); }
    export GlyphInfo getGlyphInfo(Font font, int codepoint) { return ::GetGlyphInfo(font, codepoint); }
    export Rectangle getGlyphAtlasRec(Font font, int codepoint) { return ::GetGlyphAtlasRec(font, codepoint); }

    // Text codepoints management functions
    export char* loadUTF8(const int* codepoints, int length) { return ::LoadUTF8(codepoints, length); }
    export void unloadUTF8(char* text) { ::UnloadUTF8(text); }
    export int* loadCodepoints(const char* text, int* count) { return ::LoadCodepoints(text, count); }
    export void unloadCodepoints(int* codepoints) { ::UnloadCodepoints(codepoints); }
    export int getCodepointCount(const char* text) { return ::GetCodepointCount(text); }
    export int getCodepoint(const char* text, int* codepointSize) { return ::GetCodepoint(text, codepointSize); }
    export int getCodepointNext(const char* text, int* codepointSize) { return ::GetCodepointNext(text, codepointSize); }
    export int getCodepointPrevious(const char* text, int* codepointSize) { return ::GetCodepointPrevious(text, codepointSize); }
    export const char* codepointToUTF8(int codepoint, int* utf8Size) { return ::CodepointToUTF8(codepoint, utf8Size); }

    // Text strings management functions
    export int textCopy(char* dst, const char* src) { return ::TextCopy(dst, src); }
    export bool textIsEqual(const char* text1, const char* text2) { return ::TextIsEqual(text1, text2); }
    export unsigned int textLength(const char* text) { return ::TextLength(text); }
    export const char* textFormat(const char* text, ...) { return ::TextFormat(text); }
    export const char* textSubtext(const char* text, int position, int length) { return ::TextSubtext(text, position, length); }
    export char* textReplace(char* text, const char* replace, const char* by) { return ::TextReplace(text, replace, by); }
    export char* textInsert(const char* text, const char* insert, int position) { return ::TextInsert(text, insert, position); }
    export const char* textJoin(const char** textList, int count, const char* delimiter) { return ::TextJoin(textList, count, delimiter); }
    export const char** textSplit(const char* text, char delimiter, int* count) { return ::TextSplit(text, delimiter, count); }
    export void textAppend(char* text, const char* append, int* position) { ::TextAppend(text, append, position); }
    export int textFindIndex(const char* text, const char* find) { return ::TextFindIndex(text, find); }
    export const char* textToUpper(const char* text) { return ::TextToUpper(text); }
    export const char* textToLower(const char* text) { return ::TextToLower(text); }
    export const char* textToPascal(const char* text) { return ::TextToPascal(text); }
    export int textToInteger(const char* text) { return ::TextToInteger(text); }

    // Basic geometric 3D shapes
    export void drawLine3D(Vector3 startPos, Vector3 endPos, Color color) { ::DrawLine3D(startPos, endPos, color); }
    export void drawPoint3D(Vector3 position, Color color) { ::DrawPoint3D(position, color); }
    export void drawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color) { ::DrawCircle3D(center, radius, rotationAxis, rotationAngle, color); }
    export void drawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color) { ::DrawTriangle3D(v1, v2, v3, color); }
    export void drawTriangleStrip3D(Vector3* points, int pointCount, Color color) { ::DrawTriangleStrip3D(points, pointCount, color); }
    export void drawCube(Vector3 position, float width, float height, float length, Color color) { ::DrawCube(position, width, height, length, color); }
    export void drawCubeV(Vector3 position, Vector3 size, Color color) { ::DrawCubeV(position, size, color); }
    export void drawCubeWires(Vector3 position, float width, float height, float length, Color color) { ::DrawCubeWires(position, width, height, length, color); }
    export void drawCubeWiresV(Vector3 position, Vector3 size, Color color) { ::DrawCubeWiresV(position, size, color); }
    export void drawSphere(Vector3 centerPos, float radius, Color color) { ::DrawSphere(centerPos, radius, color); }
    export void drawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color) { ::DrawSphereEx(centerPos, radius, rings, slices, color); }
    export void drawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color) { ::DrawSphereWires(centerPos, radius, rings, slices, color); }
    export void drawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) { ::DrawCylinder(position, radiusTop, radiusBottom, height, slices, color); }
    export void drawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) { ::DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color); }
    export void drawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) { ::DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color); }
    export void drawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) { ::DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color); }
    export void drawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) { ::DrawCapsule(startPos, endPos, radius, slices, rings, color); }
    export void drawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) { ::DrawCapsuleWires(startPos, endPos, radius, slices, rings, color); }
    export void drawPlane(Vector3 centerPos, Vector2 size, Color color) { ::DrawPlane(centerPos, size, color); }
    export void drawRay(Ray ray, Color color) { ::DrawRay(ray, color); }
    export void drawGrid(int slices, float spacing) { ::DrawGrid(slices, spacing); }

    // Model management functions
    export Model loadModel(const char* fileName) { return ::LoadModel(fileName); }
    export Model loadModelFromMesh(Mesh mesh) { return ::LoadModelFromMesh(mesh); }
    export bool isModelReady(Model model) { return ::IsModelReady(model); }
    export void unloadModel(Model model) { ::UnloadModel(model); }
    export BoundingBox getModelBoundingBox(Model model) { return ::GetModelBoundingBox(model); }

    // Model drawing functions
    export void drawModel(Model model, Vector3 position, float scale, Color tint) { ::DrawModel(model, position, scale, tint); }
    export void drawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) { ::DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint); }
    export void drawModelWires(Model model, Vector3 position, float scale, Color tint) { ::DrawModelWires(model, position, scale, tint); }
    export void drawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) { ::DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint); }
    export void drawBoundingBox(BoundingBox box, Color color) { ::DrawBoundingBox(box, color); }
    export void drawBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint) { ::DrawBillboard(camera, texture, position, size, tint); }
    export void drawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint) { ::DrawBillboardRec(camera, texture, source, position, size, tint); }
    export void drawBillboardPro(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint) { ::DrawBillboardPro(camera, texture, source, position, up, size, origin, rotation, tint); }
    
    // Mesh management functions
    export void uploadMesh(Mesh* mesh, bool dynamic) { ::UploadMesh(mesh, dynamic); }
    export void updateMeshBuffer(Mesh mesh, int index, const void* data, int dataSize, int offset) { ::UpdateMeshBuffer(mesh, index, data, dataSize, offset); }
    export void unloadMesh(Mesh mesh) { ::UnloadMesh(mesh); }
    export void drawMesh(Mesh mesh, Material material, Matrix transform) { ::DrawMesh(mesh, material, transform); }
    export void drawMeshInstanced(Mesh mesh, Material material, const Matrix* transforms, int instances) { ::DrawMeshInstanced(mesh, material, transforms, instances); }
    export bool exportMesh(Mesh mesh, const char* fileName) { return ::ExportMesh(mesh, fileName); }
    export BoundingBox getMeshBoundingBox(Mesh mesh) { return ::GetMeshBoundingBox(mesh); }
    export void genMeshTangents(Mesh* mesh) { ::GenMeshTangents(mesh); }

    // Mesh generation functions
    export Mesh genMeshPoly(int sides, float radius) { return ::GenMeshPoly(sides, radius); }
    export Mesh genMeshPlane(float width, float length, int resX, int resZ) { return ::GenMeshPlane(width, length, resX, resZ); }
    export Mesh genMeshCube(float width, float height, float length) { return ::GenMeshCube(width, height, length); }
    export Mesh genMeshSphere(float radius, int rings, int slices) { return ::GenMeshSphere(radius, rings, slices); }
    export Mesh genMeshHemiSphere(float radius, int rings, int slices) { return ::GenMeshHemiSphere(radius, rings, slices); }
    export Mesh genMeshCylinder(float radius, float height, int slices) { return ::GenMeshCylinder(radius, height, slices); }
    export Mesh genMeshCone(float radius, float height, int slices) { return ::GenMeshCone(radius, height, slices); }
    export Mesh genMeshTorus(float radius, float size, int radSeg, int sides) { return ::GenMeshTorus(radius, size, radSeg, sides); }
    export Mesh genMeshKnot(float radius, float size, int radSeg, int sides) { return ::GenMeshKnot(radius, size, radSeg, sides); }
    export Mesh genMeshHeightmap(Image heightmap, Vector3 size) { return ::GenMeshHeightmap(heightmap, size); }
    export Mesh genMeshCubicmap(Image cubicmap, Vector3 cubeSize) { return ::GenMeshCubicmap(cubicmap, cubeSize); }

    // Material loading/unloading functions
    export Material* loadMaterials(const char* fileName, int* materialCount) { return ::LoadMaterials(fileName, materialCount); }
    export Material loadMaterialDefault() { return ::LoadMaterialDefault(); }
    export bool isMaterialReady(Material material) { return ::IsMaterialReady(material); }
    export void unloadMaterial(Material material) { ::UnloadMaterial(material); }
    export void setMaterialTexture(Material* material, int mapType, Texture2D texture) { ::SetMaterialTexture(material, mapType, texture); }
    export void setModelMeshMaterial(Model* model, int meshId, int materialId) { ::SetModelMeshMaterial(model, meshId, materialId); }

    // Model animations loading/unloading functions
    export ModelAnimation* loadModelAnimations(const char* fileName, int* animCount) { return ::LoadModelAnimations(fileName, animCount); }
    export void updateModelAnimation(Model model, ModelAnimation anim, int frame) { ::UpdateModelAnimation(model, anim, frame); }
    export void unloadModelAnimation(ModelAnimation anim) { ::UnloadModelAnimation(anim); }
    export void unloadModelAnimations(ModelAnimation* animations, int animCount) { ::UnloadModelAnimations(animations, animCount); }
    export bool isModelAnimationValid(Model model, ModelAnimation anim) { return ::IsModelAnimationValid(model, anim); }

    // Collision detection functions
    export bool checkCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2) { return ::CheckCollisionSpheres(center1, radius1, center2, radius2); }
    export bool checkCollisionBoxes(BoundingBox box1, BoundingBox box2) { return ::CheckCollisionBoxes(box1, box2); }
    export bool checkCollisionBoxSphere(BoundingBox box, Vector3 center, float radius) { return ::CheckCollisionBoxSphere(box, center, radius); }
    export RayCollision getRayCollisionSphere(Ray ray, Vector3 center, float radius) { return ::GetRayCollisionSphere(ray, center, radius); }
    export RayCollision getRayCollisionBox(Ray ray, BoundingBox box) { return ::GetRayCollisionBox(ray, box); }
    export RayCollision getRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform) { return ::GetRayCollisionMesh(ray, mesh, transform); }
    export RayCollision getRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3) { return ::GetRayCollisionTriangle(ray, p1, p2, p3); }
    export RayCollision getRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) { return ::GetRayCollisionQuad(ray, p1, p2, p3, p4); }

    // Audio device management functions
    export void initAudioDevice() { ::InitAudioDevice(); }
    export void closeAudioDevice() { ::CloseAudioDevice(); }
    export bool isAudioDeviceReady() { return ::IsAudioDeviceReady(); }
    export void setMasterVolume(float volume) { ::SetMasterVolume(volume); }
    export float getMasterVolume() { return ::GetMasterVolume(); }

    // Wave/Sound loading/unloading functions
    export Wave loadWave(const char* fileName) { return ::LoadWave(fileName); }
    export Wave loadWaveFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) { return ::LoadWaveFromMemory(fileType, fileData, dataSize); }
    export bool isWaveReady(Wave wave) { return ::IsWaveReady(wave); }
    export Sound loadSound(const char* fileName) { return ::LoadSound(fileName); }
    export Sound loadSoundFromWave(Wave wave) { return ::LoadSoundFromWave(wave); }
    export Sound loadSoundAlias(Sound source) { return ::LoadSoundAlias(source); }
    export bool isSoundReady(Sound sound) { return ::IsSoundReady(sound); }
    export void updateSound(Sound sound, const void* data, int sampleCount) { ::UpdateSound(sound, data, sampleCount); }
    export void unloadWave(Wave wave) { ::UnloadWave(wave); }
    export void unloadSound(Sound sound) { ::UnloadSound(sound); }
    export void unloadSoundAlias(Sound alias) { ::UnloadSoundAlias(alias); }
    export bool exportWave(Wave wave, const char* fileName) { return ::ExportWave(wave, fileName); }
    export bool exportWaveAsCode(Wave wave, const char* fileName) { return ::ExportWaveAsCode(wave, fileName); }

    // Wave/Sound management functions
    export void playSound(Sound sound) { ::PlaySound(sound); }
    export void stopSound(Sound sound) { ::StopSound(sound); }
    export void pauseSound(Sound sound) { ::PauseSound(sound); }
    export void resumeSound(Sound sound) { ::ResumeSound(sound); }
    export bool isSoundPlaying(Sound sound) { return ::IsSoundPlaying(sound); }
    export void setSoundVolume(Sound sound, float volume) { ::SetSoundVolume(sound, volume); }
    export void setSoundPitch(Sound sound, float pitch) { ::SetSoundPitch(sound, pitch); }
    export void setSoundPan(Sound sound, float pan) { ::SetSoundPan(sound, pan); }
    export Wave waveCopy(Wave wave) { return ::WaveCopy(wave); }
    export void waveCrop(Wave* wave, int initSample, int finalSample) { ::WaveCrop(wave, initSample, finalSample); }
    export void waveFormat(Wave* wave, int sampleRate, int sampleSize, int channels) { ::WaveFormat(wave, sampleRate, sampleSize, channels); }
    export float* loadWaveSamples(Wave wave) { return ::LoadWaveSamples(wave); }
    export void unloadWaveSamples(float* samples) { ::UnloadWaveSamples(samples); }

    // Music management functions
    export Music loadMusicStream(const char* fileName) { return ::LoadMusicStream(fileName); }
    export Music loadMusicStreamFromMemory(const char* fileType, const unsigned char* data, int dataSize) { return ::LoadMusicStreamFromMemory(fileType, data, dataSize); }
    export bool isMusicReady(Music music) { return ::IsMusicReady(music); }
    export void unloadMusicStream(Music music) { ::UnloadMusicStream(music); }
    export void playMusicStream(Music music) { ::PlayMusicStream(music); }
    export bool isMusicStreamPlaying(Music music) { return ::IsMusicStreamPlaying(music); }
    export void updateMusicStream(Music music) { ::UpdateMusicStream(music); }
    export void stopMusicStream(Music music) { ::StopMusicStream(music); }
    export void pauseMusicStream(Music music) { ::PauseMusicStream(music); }
    export void resumeMusicStream(Music music) { ::ResumeMusicStream(music); }
    export void seekMusicStream(Music music, float position) { ::SeekMusicStream(music, position); }
    export void setMusicVolume(Music music, float volume) { ::SetMusicVolume(music, volume); }
    export void setMusicPitch(Music music, float pitch) { ::SetMusicPitch(music, pitch); }
    export void setMusicPan(Music music, float pan) { ::SetMusicPan(music, pan); }
    export float getMusicTimeLength(Music music) { return ::GetMusicTimeLength(music); }
    export float getMusicTimePlayed(Music music) { return ::GetMusicTimePlayed(music); }

    // AudioStream management functions
    export AudioStream loadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels) { return ::LoadAudioStream(sampleRate, sampleSize, channels); }
    export bool isAudioStreamReady(AudioStream stream) { return ::IsAudioStreamReady(stream); }
    export void unloadAudioStream(AudioStream stream) { ::UnloadAudioStream(stream); }
    export void updateAudioStream(AudioStream stream, const void* data, int frameCount) { ::UpdateAudioStream(stream, data, frameCount); }
    export bool isAudioStreamProcessed(AudioStream stream) { return ::IsAudioStreamProcessed(stream); }
    export void playAudioStream(AudioStream stream) { ::PlayAudioStream(stream); }
    export void pauseAudioStream(AudioStream stream) { ::PauseAudioStream(stream); }
    export void resumeAudioStream(AudioStream stream) { ::ResumeAudioStream(stream); }
    export bool isAudioStreamPlaying(AudioStream stream) { return ::IsAudioStreamPlaying(stream); }
    export void stopAudioStream(AudioStream stream) { ::StopAudioStream(stream); }
    export void setAudioStreamVolume(AudioStream stream, float volume) { ::SetAudioStreamVolume(stream, volume); }
    export void setAudioStreamPitch(AudioStream stream, float pitch) { ::SetAudioStreamPitch(stream, pitch); }
    export void setAudioStreamPan(AudioStream stream, float pan) { ::SetAudioStreamPan(stream, pan); }
    export void setAudioStreamBufferSizeDefault(int size) { ::SetAudioStreamBufferSizeDefault(size); }
    export void setAudioStreamCallback(AudioStream stream, AudioCallback callback) { ::SetAudioStreamCallback(stream, callback); }
    export void attachAudioStreamProcessor(AudioStream stream, AudioCallback processor) { ::AttachAudioStreamProcessor(stream, processor); }
    export void detachAudioStreamProcessor(AudioStream stream, AudioCallback processor) { ::DetachAudioStreamProcessor(stream, processor); }
    export void attachAudioMixedProcessor(AudioCallback processor) { ::AttachAudioMixedProcessor(processor); }
    export void detachAudioMixedProcessor(AudioCallback processor) { ::DetachAudioMixedProcessor(processor); }


    /** Math **/
        // Utils math
    export float clamp(float value, float min, float max) { return ::Clamp(value, min, max); }
    export float lerp(float start, float end, float amount) { return ::Lerp(start, end, amount); }
    export float normalize(float value, float start, float end) { return ::Normalize(value, start, end); }
    export float remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd) { return ::Remap(value, inputStart, inputEnd, outputStart, outputEnd); }
    export float wrap(float value, float min, float max) { return ::Wrap(value, min, max); }
    export int floatEquals(float x, float y) { return ::FloatEquals(x, y); }

    // Vector2 Math
    export Vector2 vector2Zero(void) { return ::Vector2Zero(); }
    export Vector2 vector2One(void) { return ::Vector2One(); }
    export Vector2 vector2Add(Vector2 v1, Vector2 v2) { return ::Vector2Add(v1, v2); }
    export Vector2 vector2AddValue(Vector2 v, float add) { return ::Vector2AddValue(v, add); }
    export Vector2 vector2Subtract(Vector2 v1, Vector2 v2) { return ::Vector2Subtract(v1, v2); }
    export Vector2 vector2SubtractValue(Vector2 v, float sub) { return ::Vector2SubtractValue(v, sub); }
    export float vector2Length(Vector2 v) { return ::Vector2Length(v); }
    export float vector2LengthSqr(Vector2 v) { return ::Vector2LengthSqr(v); }
    export float vector2DotProduct(Vector2 v1, Vector2 v2) { return ::Vector2DotProduct(v1, v2); }
    export float vector2Distance(Vector2 v1, Vector2 v2) { return ::Vector2Distance(v1, v2); }
    export float vector2DistanceSqr(Vector2 v1, Vector2 v2) { return ::Vector2DistanceSqr(v1, v2); }
    export float vector2Angle(Vector2 v1, Vector2 v2) { return ::Vector2Angle(v1, v2); }
    export float vector2LineAngle(Vector2 start, Vector2 end) { return ::Vector2LineAngle(start, end); }
    export Vector2 vector2Scale(Vector2 v, float scale) { return ::Vector2Scale(v, scale); }
    export Vector2 vector2Multiply(Vector2 v1, Vector2 v2) { return ::Vector2Multiply(v1, v2); }
    export Vector2 vector2Negate(Vector2 v) { return ::Vector2Negate(v); }
    export Vector2 vector2Divide(Vector2 v1, Vector2 v2) { return ::Vector2Divide(v1, v2); }
    export Vector2 vector2Normalize(Vector2 v) { return ::Vector2Normalize(v); }
    export Vector2 vector2Transform(Vector2 v, Matrix mat) { return ::Vector2Transform(v, mat); }
    export Vector2 vector2Lerp(Vector2 v1, Vector2 v2, float amount) { return ::Vector2Lerp(v1, v2, amount); }
    export Vector2 vector2Reflect(Vector2 v, Vector2 normal) { return ::Vector2Reflect(v, normal); }
    export Vector2 vector2Rotate(Vector2 v, float angle) { return ::Vector2Rotate(v, angle); }
    export Vector2 vector2MoveTowards(Vector2 v, Vector2 target, float maxDistance) { return ::Vector2MoveTowards(v, target, maxDistance); }
    export Vector2 vector2Invert(Vector2 v) { return ::Vector2Invert(v); }
    export Vector2 vector2Clamp(Vector2 v, Vector2 min, Vector2 max) { return ::Vector2Clamp(v, min, max); }
    export Vector2 vector2ClampValue(Vector2 v, float min, float max) { return ::Vector2ClampValue(v, min, max); }
    export int vector2Equals(Vector2 p, Vector2 q) { return ::Vector2Equals(p, q); }

    // Vector3 Math
    export Vector3 vector3Zero(void) { return ::Vector3Zero(); }
    export Vector3 vector3One(void) { return ::Vector3One(); }
    export Vector3 vector3Add(Vector3 v1, Vector3 v2) { return ::Vector3Add(v1, v2); }
    export Vector3 vector3AddValue(Vector3 v, float add) { return ::Vector3AddValue(v, add); }
    export Vector3 vector3Subtract(Vector3 v1, Vector3 v2) { return ::Vector3Subtract(v1, v2); }
    export Vector3 vector3SubtractValue(Vector3 v, float sub) { return ::Vector3SubtractValue(v, sub); }
    export Vector3 vector3Scale(Vector3 v, float scalar) { return ::Vector3Scale(v, scalar); }
    export Vector3 vector3Multiply(Vector3 v1, Vector3 v2) { return ::Vector3Multiply(v1, v2); }
    export Vector3 vector3CrossProduct(Vector3 v1, Vector3 v2) { return ::Vector3CrossProduct(v1, v2); }
    export Vector3 vector3Perpendicular(Vector3 v) { return ::Vector3Perpendicular(v); }
    export float vector3Length(const Vector3 v) { return ::Vector3Length(v); }
    export float vector3LengthSqr(const Vector3 v) { return ::Vector3LengthSqr(v); }
    export float vector3DotProduct(Vector3 v1, Vector3 v2) { return ::Vector3DotProduct(v1, v2); }
    export float vector3Distance(Vector3 v1, Vector3 v2) { return ::Vector3Distance(v1, v2); }
    export float vector3DistanceSqr(Vector3 v1, Vector3 v2) { return ::Vector3DistanceSqr(v1, v2); }
    export float vector3Angle(Vector3 v1, Vector3 v2) { return ::Vector3Angle(v1, v2); }
    export Vector3 vector3Negate(Vector3 v) { return ::Vector3Negate(v); }
    export Vector3 vector3Divide(Vector3 v1, Vector3 v2) { return ::Vector3Divide(v1, v2); }
    export Vector3 vector3Normalize(Vector3 v) { return ::Vector3Normalize(v); }
    export Vector3 vector3Transform(Vector3 v, Matrix mat) { return ::Vector3Transform(v, mat); }
    export Vector3 vector3Lerp(Vector3 v1, Vector3 v2, float amount) { return ::Vector3Lerp(v1, v2, amount); }
    export Vector3 vector3Reflect(Vector3 v, Vector3 normal) { return ::Vector3Reflect(v, normal); }
    export Vector3 vector3Min(Vector3 v1, Vector3 v2) { return ::Vector3Min(v1, v2); }
    export Vector3 vector3Max(Vector3 v1, Vector3 v2) { return ::Vector3Max(v1, v2); }
    export Vector3 vector3Barycenter(Vector3 p, Vector3 a, Vector3 b, Vector3 c) { return ::Vector3Barycenter(p, a, b, c); }
    export Vector3 vector3Unproject(Vector3 source, Matrix projection, Matrix view) { return ::Vector3Unproject(source, projection, view); }
    export float3 vector3ToFloatV(Vector3 v) { return ::Vector3ToFloatV(v); }
    export Vector3 vector3Invert(Vector3 v) { return ::Vector3Invert(v); }
    export Vector3 vector3Clamp(Vector3 v, Vector3 min, Vector3 max) { return ::Vector3Clamp(v, min, max); }
    export Vector3 vector3ClampValue(Vector3 v, float min, float max) { return ::Vector3ClampValue(v, min, max); }
    export int vector3Equals(Vector3 p, Vector3 q) { return ::Vector3Equals(p, q); }
    export Vector3 vector3Refract(Vector3 v, Vector3 n, float r) { return ::Vector3Refract(v, n, r); }

    // Quaternion Math
    export Vector4 quaternionIdentity(void) { return ::QuaternionIdentity(); }
    export float quaternionLength(Vector4 q) { return ::QuaternionLength(q); }
    export Vector4 quaternionNormalize(Vector4 q) { return ::QuaternionNormalize(q); }
    export Vector4 quaternionInvert(Vector4 q) { return ::QuaternionInvert(q); }
    export Vector4 quaternionMultiply(Vector4 q1, Vector4 q2) { return ::QuaternionMultiply(q1, q2); }
    export Vector4 quaternionScale(Vector4 q, float mul) { return ::QuaternionScale(q, mul); }
    export Vector4 quaternionDivide(Vector4 q1, Vector4 q2) { return ::QuaternionDivide(q1, q2); }
    export Vector4 quaternionLerp(Vector4 q1, Vector4 q2, float amount) { return ::QuaternionLerp(q1, q2, amount); }
    export Vector4 quaternionNlerp(Vector4 q1, Vector4 q2, float amount) { return ::QuaternionNlerp(q1, q2, amount); }
    export Vector4 quaternionSlerp(Vector4 q1, Vector4 q2, float amount) { return ::QuaternionSlerp(q1, q2, amount); }
    export Vector4 quaternionFromVector3ToVector3(Vector3 from, Vector3 to) { return ::QuaternionFromVector3ToVector3(from, to); }
    export Vector4 quaternionFromMatrix(Matrix mat) { return ::QuaternionFromMatrix(mat); }
    export Matrix quaternionToMatrix(Vector4 q) { return ::QuaternionToMatrix(q); }
    export Vector4 quaternionFromAxisAngle(Vector3 axis, float angle) { return ::QuaternionFromAxisAngle(axis, angle); }
    export void quaternionToAxisAngle(Vector4 q, Vector3* outAxis, float* outAngle) { ::QuaternionToAxisAngle(q, outAxis, outAngle); }
    export Vector4 quaternionFromEuler(float pitch, float yaw, float roll) { return ::QuaternionFromEuler(pitch, yaw, roll); }
    export Vector3 quaternionToEuler(Vector4 q) { return ::QuaternionToEuler(q); }
    export Vector4 quaternionTransform(Vector4 q, Matrix mat) { return ::QuaternionTransform(q, mat); }
    export int quaternionEquals(Vector4 p, Vector4 q) { return ::QuaternionEquals(p, q); }

}