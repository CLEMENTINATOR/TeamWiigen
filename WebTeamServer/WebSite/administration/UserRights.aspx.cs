using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebFramework;
using WebSiteModel;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;

namespace WebSite.administration
{
    public partial class UserRights : PageBase
    {
        protected override void OnPreInit(EventArgs e)
        {
            Master.Title = "User Rights";
            this.Master.Section = "Administration";
            RequiredRights.Add(RightList.UsersRights);
            base.OnInit(e);
        }

        protected int UserId
        {
            get
            {
                return int.Parse(Request.Params["user"]);
            }
        }

        #region TreeView management
        protected void trvRights_Init(object sender, EventArgs e)
        {
            DataSet source = new DataSet();
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["tw_web_ado"].ConnectionString))
            {
                using (SqlCommand command = new SqlCommand("GET_USER_RIGHTS", connection))
                {
                    command.CommandType = CommandType.StoredProcedure;
                    command.Parameters.Add("USR_ID", SqlDbType.Int).Value = UserId;
                    using (SqlDataAdapter adapter = new SqlDataAdapter(command))
                    {
                        connection.Open();
                        adapter.Fill(source);
                    }
                }
            }
            trvRights.DataSource = new HierarchicalDataSet(source, "RIG_ID", "RIG_PARENT_ID");
            trvRights.DataBind();

        }

        protected void trvRights_TreeNodeDataBound(object sender, TreeNodeEventArgs e)
        {
            DataRowView data = e.Node.DataItem as DataRowView;
            e.Node.Checked = (1 == (int)data["RIG_SELECTED"]);
        }

        protected void trvRights_TreeNodeCheckChanged(object sender, TreeNodeEventArgs e)
        {
            TreeNode node = e.Node;

            if (node.Checked)
                do
                {
                    node = node.Parent;
                } while (CheckParent(node));
            else
                CheckChilds(node);

        }

        private void CheckChilds(TreeNode node)
        {
            foreach (TreeNode child in node.ChildNodes)
            {
                if (child.Checked)
                {
                    child.Checked = false;
                    CheckChilds(child);
                }
            }
        }

        private bool CheckParent(TreeNode treeNode)
        {
            if (treeNode == null)
                return false;

            bool toCheck = false;
            foreach (TreeNode child in treeNode.ChildNodes)
                if (child.Checked)
                {
                    toCheck = true;
                    break;
                }

            if (toCheck == treeNode.Checked)
                return false;

            if (toCheck)
            {
                treeNode.Checked = toCheck;
                return true;
            }

            return false;
        }
        #endregion

        private User _currentUser;
        public User CurrentUser
        {
            get
            {
                if (_currentUser == null)
                    _currentUser = (from u in DbInstance.Users
                                    where u.Id == UserId
                                    select u).First();

                return _currentUser;
            }
        }

        protected void btnValider_Click(object sender, EventArgs e)
        {
            CurrentUser.Rights.Load();
            CurrentUser.Rights.Clear();
            foreach (TreeNode roots in trvRights.Nodes)
                AssociateRights(roots);
            DbInstance.SaveChanges();
            Response.Redirect("~/administration/Users.aspx", false);
        }

        private void AssociateRights(TreeNode node)
        {
            if (node.Checked)
            {
                int rightId = int.Parse(node.Value);
                Right nodeRight = (from r in DbInstance.Rights
                                   where r.Id == rightId
                                   select r).First();
                CurrentUser.Rights.Add(nodeRight);
            }
            foreach (TreeNode child in node.ChildNodes)
                AssociateRights(child);
        }
    }
}