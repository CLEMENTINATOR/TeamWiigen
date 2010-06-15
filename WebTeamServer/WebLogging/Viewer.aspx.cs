using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Microsoft.Reporting.WebForms;
using System.Data;
using WebLogging.data.LogsDSTableAdapters;
using System.Data.SqlClient;
using System.Configuration;

namespace WebLogging
{
    public partial class Viewer : System.Web.UI.Page
    {
        protected void btnGoReport_Click(object sender, EventArgs e)
        {
            if (!Page.IsValid)
                return;

            ReportDataSource source;
            int tempInt;

            int? LOG_LTY_ID = int.TryParse(ddlLogType.SelectedValue, out tempInt) ? tempInt : (int?)null;
            int? LOG_APV_ID = int.TryParse(ddlVersion.SelectedValue, out tempInt) ? tempInt : (int?)null;
            int? APP_ID = int.TryParse(ddlApplication.SelectedValue, out tempInt) ? tempInt : (int?)null;
            DateTime? startDate = String.IsNullOrEmpty(tbxStartDate.Text) ? (DateTime?)null : DateTime.Parse(tbxStartDate.Text);
            DateTime? endDate = String.IsNullOrEmpty(tbxEndDate.Text) ? (DateTime?)null : DateTime.Parse(tbxEndDate.Text);
            string ipFilter = string.IsNullOrEmpty(tbxIP.Text) ? null : tbxIP.Text;

            using (SEL_LOGTableAdapter adapter = new SEL_LOGTableAdapter())
            {
                 source = new ReportDataSource("LogDS",(DataTable)adapter.GetData(LOG_LTY_ID, LOG_APV_ID, startDate, endDate, APP_ID, ipFilter));
            }

            
            report.LocalReport.DataSources.Clear();
            report.LocalReport.DataSources.Add(source);
            report.LocalReport.Refresh();
            report.Visible = true;
        }

        protected void ddlLogType_Init(Object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["tw_sql"].ConnectionString))
            {
                using (SqlDataAdapter command = new SqlDataAdapter("SELECT NULL AS LTY_ID, '(All)' AS LTY_VALUE UNION SELECT LTY_ID, LTY_VALUE FROM LOG_TYPE", connection))
                {
                    DataTable source = new DataTable();
                    connection.Open();
                    command.Fill(source);
                    ddlLogType.DataSource = source;
                    ddlLogType.DataBind();
                }
            }
        }

        protected void ddlApplication_Init(Object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["tw_sql"].ConnectionString))
            {
                using (SqlDataAdapter command = new SqlDataAdapter("SELECT NULL AS APP_ID, '(All)' AS APP_NAME UNION SELECT APP_ID, APP_NAME FROM APPLICATIONS ORDER BY APP_NAME", connection))
                {
                    DataTable source = new DataTable();
                    connection.Open();
                    command.Fill(source);
                    ddlApplication.DataSource = source;
                    ddlApplication.DataBind();
                }
            }
        }

        protected void ddlApplication_SelectedIndexChanged(Object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(ddlApplication.SelectedValue))
            {
                using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["tw_sql"].ConnectionString))
                {
                    using (SqlDataAdapter command = new SqlDataAdapter("SELECT NULL AS APV_ID, '(All)' AS APV_VALUE UNION SELECT APV_ID, APV_VALUE FROM APPLICATION_VERSION WHERE APV_APP_ID = " + ddlApplication.SelectedValue + " ORDER BY APV_VALUE", connection))
                    {
                        DataTable source = new DataTable();
                        connection.Open();
                        command.Fill(source);
                        ddlVersion.DataSource = source;
                        ddlVersion.DataBind();
                    }
                }
                ddlVersion.Enabled = true;
            }
            else
            {
                ddlVersion.SelectedIndex = 0;
                ddlVersion.DataSource = null;
                ddlVersion.DataBind();
                ddlVersion.Enabled = false;
            }
        }

        protected void ValidateDate(object source, ServerValidateEventArgs args)
        {
            DateTime testDate;
            args.IsValid = DateTime.TryParse(args.Value, out testDate);
        }
    }
}