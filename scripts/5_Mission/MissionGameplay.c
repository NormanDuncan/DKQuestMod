modded class MissionGameplay 
{
    override UIScriptedMenu CreateScriptedMenu(int id)
    {
        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        if (id == 123456)
        {
            menu = new MyQuestMenu();
            menu.SetID(id);
        }

        return menu;
    }

    override void OnMenuEnter(int menu_id, Param params) {
        super.OnMenuEnter(menu_id, params);

        if (menu_id == 123456 && params) {
            Param2<string, string> data = Param2<string, string>.Cast(params);
            
            // Находим только что созданное меню через UIManager
            MyQuestMenu qMenu = MyQuestMenu.Cast(GetGame().GetUIManager().GetMenu());
            if (qMenu && data)
            {
                // Заполняем его данными
                qMenu.SetContent(data.param1, data.param2);
            }
        }
    }
}
