using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebFramework;
using System.Web.UI.HtmlControls;

namespace WebSite
{
    public partial class MasterPage : System.Web.UI.MasterPage
    {
        public string Title { get; set; }
        public string Section { get; set; }
        public HtmlForm Formulaire { get { return form1; } }

        protected override void OnLoad(EventArgs e)
        {
            rptFrontMenu.DataSource = MenuManager.Instance.GetFrontMenuList(WebSession.User);
            rptFrontMenu.DataBind();

            if (!String.IsNullOrEmpty(Section))
            {
                rptSubMenu.DataSource = MenuManager.Instance.GetSideMenuList(WebSession.User, Section);
                rptSubMenu.DataBind();
            }
            base.OnLoad(e);
        }
    }
}