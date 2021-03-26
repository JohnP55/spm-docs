/*
    setup_data defines the structure of the dat files in "./setup/"
    and handles the item-spawning side of them
    See also npcdrv.h and setupfiles.md
*/

// v0-5 unknown, v0-4 don't have support for items, v0 is unused
// Skawo has the size of the enemy structs for other versions and an unusual unknown field in v1 documented at
// https://github.com/skawo/Super-Paper-Mario-Level-Editor-Randomizer/blob/c715b6e9408ff8b1052f4bc9cd8dc33ea717f16a/Super%20Paper%20Mario%20Randomizer/Common/SPM.cs#L25

typedef struct {
/* 0x00 */ int instanceId; // ignored if 0
/* 0x04 */ // 0x4-5f
} MiscSetupDataV6; // total size 0x60

typedef struct {
/* 0x00 */ Vec3 pos;
/* 0x0C */ int type; // nTemplateNo, index into npcEnemyTemplates
/* 0x10 */ MiscSetupDataV6 misc;
} SetupEnemyV6; // total size 0x70

typedef struct {
/* 0x0000 */ uint16_t version;
/* 0x0002 */ // padding 0x2-3
/* 0x0004 */ SetupEnemyV6 enemies[100];
} SetupFileV6; // total size 0x2bc4

typedef struct {
/* 0x0 */ uint16_t flags; // 0x10 and 0x1 required to spawn, others unused
/* 0x2 */ uint16_t type; // only 0 is supported, which is a coin
/* 0x4 */ Vec3 pos;
} SetupItem; // total size 0x8

typedef struct {
/* 0x0000 */ SetupFileV6 main;
/* 0x2BC4 */ int itemCount;
/* 0x2BC8 */ int itemVersion; // 20051201
/* 0x2BCC */ SetupItem items[]; // itemCount items
} SetupFileV6WithItems; // variable total size

typedef struct {
/* 0x0 */ uint16_t id; // only 0 is used
/* 0x0 */ uint16_t itemTeplateId; // index into setupItemTemplates
} SetupItemTemplate;

SetupItemTemplate setupItemTemplates[1]; // 805adf08, only contains id 0 - a coin

/*
    Takes a pointer to the item list of a setup file & its length and spawns them 
*/
void setupSpawnItems(int count, SetupItem * items); // 80029680

/*
    Takes a pointer to a setup file and returns the number of items in it, the
    version of the item data and the pointer to the array of items
    
    Returns all 0s for setup files that aren't v5 or v6, or for v5 & v6 that
    don't have any item data in them (technically reads uninitialised memory)
*/
void setupReadItemInfo(void * file, int * count, int * version, SetupItem ** data); // 80029730
