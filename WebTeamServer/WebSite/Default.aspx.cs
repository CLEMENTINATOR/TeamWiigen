using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebFramework;

namespace WebSite
{
    public partial class Default : PageBase
    {
        protected override void OnPreInit(EventArgs e)
        {
            Master.Title = "Welcome";
            base.OnPreInit(e);
        }
    }
}