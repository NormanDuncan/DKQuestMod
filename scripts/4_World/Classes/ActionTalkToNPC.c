class ActionTalkToNPC : ActionInteractBase
{
    void ActionTalkToNPC() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Поговорить c Данилом Колбасенко";
    }

    
    override bool HasTarget()
    {
        return true;
    }

    override bool HasProgress()
    {
        return false;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTObject(4.0);
        m_ConditionItem = new CCINone;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return target.GetObject().IsInherited(QuestGiverNPC);
    }

    override void OnStartServer(ActionData action_data) {
        super.OnStartServer(action_data);

        QuestGiverNPC npc = QuestGiverNPC.Cast(action_data.m_Target.GetObject());

        if (!npc || !npc.m_Data) return;

        PlayerIdentity targetId = action_data.m_Player.GetIdentity();

        string title = npc.m_Data.Title;
        string desc = npc.m_Data.Description;
        
        if (targetId) {
            auto params = new Param2<string, string>(title, desc);
            GetGame().RPCSingleParam(npc, 73985, params, true, targetId);
            
            Print("--- [SERVER] RPC отправлен игроку: " + targetId.GetName());
        } 
        else
        {
            GetGame().GetUIManager.EnterScriptedMenu(123456, params);
            Print("--- [OFFLINE] Данные сохранены в MissionGameplay, меню открыто.");
        }
    }

}
