using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebFramework;
using WebSiteModel;

namespace WebSite.administration
{
    public partial class Users : PageBase
    {
        protected override void OnPreInit(EventArgs e)
        {
            Master.Title = "User management";
            this.Master.Section = "Administration";
            RequiredRights.Add(RightList.Users);
            base.OnInit(e);
        }

        protected override void OnLoad(EventArgs e)
        {
            if (!IsPostBack)
            {
                grvUsers.DataSource = from u in DbInstance.Users
                                      select u;
                grvUsers.DataBind();
            }
            base.OnLoad(e);
        }

        protected void lnkNewUser_Init(object sender, EventArgs e)
        {
            lnkNewUser.Visible = WebSession.User.AllUserRights.Contains(RightList.CreateUsers);
        }

        protected void btnRecherche_Click(object sender, EventArgs e)
        {
            grvUsers.DataSource = from u in DbInstance.Users
                                  where (String.IsNullOrEmpty(tbxLogin.Text.Trim()) || u.Login.Contains(tbxLogin.Text.Trim()))
                                     && (String.IsNullOrEmpty(tbxMail.Text.Trim()) || u.Mail.Contains(tbxMail.Text.Trim()))
                                  select u;
            grvUsers.DataBind();
        }

        protected void grvUsers_Init(object sender, EventArgs e)
        {
            grvUsers.Columns[grvUsers.Columns.Count - 1].Visible = WebSession.User.AllUserRights.Contains(RightList.DeleteUsers);
            grvUsers.Columns[grvUsers.Columns.Count - 2].Visible = WebSession.User.AllUserRights.Contains(RightList.UsersRoles);
            grvUsers.Columns[grvUsers.Columns.Count - 3].Visible = WebSession.User.AllUserRights.Contains(RightList.UsersRights);
        }

        protected void grvUsers_RowCommand(object sender, GridViewCommandEventArgs e)
        {
            switch (e.CommandName)
            {
                case "sup":
                    var users = from u in DbInstance.Users
                                where u.Id == int.Parse(e.CommandArgument.ToString())
                                select u;
                    if (users.Count() == 1)
                        DbInstance.DeleteObject(users.First());
                    break;
            }
        }
    }
}