using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;

namespace WebLogging
{
    public partial class Logger : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["tw_sql"].ConnectionString))
                {
                    using (SqlCommand command = new SqlCommand("INS_LOG", connection))
                    {
                        command.CommandType = System.Data.CommandType.StoredProcedure;
                        command.Parameters.Add("APP_NAME", System.Data.SqlDbType.NVarChar, 50).Value = Request.Params["application"];
                        command.Parameters.Add("APV_VALUE", System.Data.SqlDbType.NVarChar, 10).Value = Request.Params["version"];
                        command.Parameters.Add("LTY_CODE", System.Data.SqlDbType.NVarChar, 3).Value = Request.Params["type"];
                        command.Parameters.Add("LOG_MESSAGE", System.Data.SqlDbType.NVarChar, 255).Value = Request.Params["message"];
                        command.Parameters.Add("LOG_SOURCE", System.Data.SqlDbType.NVarChar, 255).Value = Request.Params["file"];
                        command.Parameters.Add("LOG_LINE", System.Data.SqlDbType.Int).Value = Request.Params["line"];
                        command.Parameters.Add("LOG_USER_IP", System.Data.SqlDbType.VarChar, 15).Value = Request.UserHostAddress; 
                        connection.Open();
                        command.ExecuteNonQuery();
                    }
                }
            }
            catch { }
        }
    }
}