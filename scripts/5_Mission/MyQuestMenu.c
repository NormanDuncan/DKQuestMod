class MyQuestMenu extends UIScriptedMenu
{
    private Widget m_Root;
    private ButtonWidget m_CloseBtn;
    private TextWidget m_Title;
    private MultilineTextWidget m_Description;

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("DKQuestMod/GUI/layouts/menu.layout");

        if (m_Root)
        {
            m_CloseBtn = ButtonWidget.Cast(m_Root.FindAnyWidget("btn_close"));
            m_Title = TextWidget.Cast(m_Root.FindAnyWidget("txt_title"));
            m_Description = MultilineTextWidget.Cast(m_Root.FindAnyWidget("txt_desc"));
        }
        
        return m_Root;
    }

    void FillData(string title, string text)
    {
        if (m_Title) m_Title.SetText(title);
        if (m_Description) m_Description.SetText(text);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        super.OnClick(w, x, y, button);

        if (w == m_CloseBtn)
        {
            Close(); // Закрыть меню
            return true;
        }
        return false;
    }

    override void OnShow()
    {
        super.OnShow();
        if (GetGame().GetMission())
            GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        if (GetGame().GetInput())
            GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowCursor(true);
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetMission().PlayerControlEnable(true);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowCursor(false);
    }

    override bool OnKeyPress(Widget w, int x, int y, int key)
    {
        super.OnKeyPress(w, x, y, key);
        
        // KeyCode 1 — это клавиша ESC
        if (key == KeyCode.KC_ESCAPE)
        {
            // Закрываем меню через UIManager, чтобы сработал OnHide
            GetGame().GetUIManager().HideScriptedMenu(this);
            return true;
        }
        
        return false;
    }
}
