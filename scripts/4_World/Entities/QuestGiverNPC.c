class QuestGiverNPC : PlayerBase 
{
    string m_QuestID = "default_quest";
    const int RPC_OPEN_NPC_MENU = 73985;
    ref QuestData m_Data;

    override void Init() {
        super.Init();
        if (GetGame().IsServer()) {
            SetAllowDamage(false);
            LoadQuestConfig();
        }
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) 
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (rpc_type == 73985 && GetGame().IsClient()) {

            Param2<string, string> data;
            if (!ctx.Read(data)) return;

            GetGame().GetUIManager().EnterScriptedMenu(123456, data);
            Print("--- [CLIENT] RPC получен, данные в MissionGameplay обновлены.");
        }
    }

    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);
        AddAction(ActionTalkToNPC, InputActionMap);
    }

    void SetQuestID(string id) { m_QuestID = id; }
    string GetQuestID() { return m_QuestID; }

    override string GetDisplayName()
    {
        return "Данил Колбасенко";
    }

    override void GetActions(typename action_input_type, out array<ActionBase_Basic> actions)
    {
        super.GetActions(action_input_type, actions);

        if (action_input_type == InteractActionInput)
        {
            PlayerBase player = PlayerBase.Cast(GetGame().  GetPlayer());
            if (player)
            {
                ActionBase_Basic myAction = player.GetActionManager().GetAction (ActionTalkToNPC);
                if (myAction)
                {
                    actions.Insert(myAction);
                }
            }
        }
    }

    void LoadQuestConfig()
    {
        string folder = "$profile:DKQuestMod";
        string path = folder + "/quest_danil.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        m_Data = new QuestData();

        if (FileExist(path))
        {
            JsonFileLoader<QuestData>.JsonLoadFile(path, m_Data);

            if (m_Data.Title == "" && m_Data.Description == "")
            {
                m_Data.Title = "Нет заданий";
                m_Data.Description = "На данный момент у Данила Колбасенко нет для вас поручений. Приходите позже!";
            }
            Print("--- [SERVER] Данные квеста загружены успешно.");
        }
        else
        {
            m_Data.Title = "Привет, Выживший!";
            m_Data.Description = "Это тестовый квест. Если ты видишь этот текст, значит JSON создался автоматически в папке профиля сервера.";
        
            JsonFileLoader<QuestData>.JsonSaveFile(path, m_Data);
            Print("--- [SERVER] Файл не найден. Создан шаблон: " + path);
        }
    }
}
