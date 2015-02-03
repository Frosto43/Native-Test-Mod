#include <jni.h>
#include <mcpelauncher.h>
#include <dlfcn.h>
#include <android/log.h>

static void (*Tile$Tile)(Tile*, int, std::string const&, void*);
static void (*TileItem$TileItem)(Item*, int);
static Tile** Tile*tiles;
static void** TileItem*vtable:
std::map <std::string, std::string>* I18n$strings;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
	dlerror();

	Tile$Tile = (void (*)(Tile*, int, std::string, void*)) dlsym(handle, "_ZN4TileC2EiSsPK8Material");
	Tile$tiles = (Tile**) dlsym(handle, "_ZTV8Tile5tilesE");

	TileItem$TileItem = (void (*)(TileItem*, int)) dlsym(handle, "_ZN8TileItemC2Ei");
	TileItem$vtable = (void**) ((int) dlsym(handle, "_ZTV8TileItem") + 8);

	I18n$strings = (std::map <std::string, std::string>*) dlsym(handle, "_ZN4I18n8_stringsE");

	const char* error = dlerror();
	if(error) __android_log_print(ANDROID_LOG_INFO, "MY MOD", "dlerror: %s", error);

	return JNI_VERSION_1_2;
}