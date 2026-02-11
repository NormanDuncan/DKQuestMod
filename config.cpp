class CfgPatches {
    class DKQuestMod {
        units[] = {"QuestGiverNPC"};
        weapons[] = {};
        requiredAddons[] = {
            "DZ_Data", 
            "DZ_Characters", 
            "DZ_Scripts" // Обязательно для работы скриптов
        };
    };
}; 

class CfgMods {
    class DKQuestMod {
        dir = "DKQuestMod";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "DKQuestMod";
        credits = "";
        author = "zelenka";
        version = "1.0";
        extra = 0;
        type = "mod";

        dependencies[] = { "World", "Mission" }; // Указываем, что влияем на мир

        class defs {
            class worldScriptModule {
                value = "";
                // Здесь мы говорим игре, где искать наши .c файлы
                files[] = {"DKQuestMod/scripts/4_World"};
            };
            class missionScriptModule {
                value = "";
                files[] = {"DKQuestMod/scripts/5_Mission"}; // Добавляем путь к 5-й миссии
            };
        };
    };
};

class CfgVehicles {
    class SurvivorM_Mirek; 
    class QuestGiverNPC: SurvivorM_Mirek {
        scope = 2; // Разрешить спавн
        displayName = "Данил Колбасенко";
    };
};
