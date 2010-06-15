<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Viewer.aspx.cs" Inherits="WebLogging.Viewer" %>

<%@ Register Assembly="Microsoft.ReportViewer.WebForms, Version=10.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
    Namespace="Microsoft.Reporting.WebForms" TagPrefix="rsweb" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <ajax:ToolkitScriptManager ID="scriptManager" runat="server" />
    <div>
        <asp:Table ID="tblParameters" runat="server" SkinID="criteres">
            <asp:TableRow>

                <asp:TableCell Text="Log type:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:DropDownList ID="ddlLogType" runat="server" DataTextField="LTY_VALUE" DataValueField="LTY_ID"
                        OnInit="ddlLogType_Init" />
                </asp:TableCell>

                <asp:TableCell Text="Start date:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:CustomValidator ID="cvlStartDate" runat="server" Text="!" Display="Dynamic" ControlToValidate="tbxStartDate" ValidateEmptyText="false" OnServerValidate="ValidateDate" />
                    <asp:TextBox ID="tbxStartDate" runat="server" />&nbsp;
                    <asp:ImageButton ID="imgStartDate" runat="server" ImageUrl="~/images/calendar.png" />
                    <ajax:CalendarExtender ID="calStartDate" runat="server" TargetControlID="tbxStartDate"
                        PopupButtonID="imgStartDate" ClearTime="true" />
                    <ajax:MaskedEditExtender ID="meeStartDate" runat="server" TargetControlID="tbxStartDate"
                        Mask="99/99/9999" MaskType="Date" />
                </asp:TableCell><asp:TableCell Text="End date:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:CustomValidator ID="cvlEndDate" runat="server" Text="!" Display="Dynamic" ControlToValidate="tbxEndDate" ValidateEmptyText="false" OnServerValidate="ValidateDate" />
                    <asp:TextBox ID="tbxEndDate" runat="server" />&nbsp;
                    <asp:ImageButton ID="imgEndDate" runat="server" ImageUrl="~/images/calendar.png" />
                    <ajax:CalendarExtender ID="calEndDate" runat="server" TargetControlID="tbxEndDate"
                        PopupButtonID="imgEndDate" ClearTime="true" />
                    <ajax:MaskedEditExtender ID="meeEndDate" runat="server" TargetControlID="tbxEndDate"
                        Mask="99/99/9999" MaskType="Date" />
                </asp:TableCell><asp:TableCell Text="IP filter:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:TextBox ID="tbxIP" runat="server" MaxLength="15" />
                </asp:TableCell></asp:TableRow><asp:TableRow>

                <asp:TableCell Text="Application:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:DropDownList ID="ddlApplication" runat="server" DataValueField="APP_ID" DataTextField="APP_NAME"
                        OnInit="ddlApplication_Init" OnSelectedIndexChanged="ddlApplication_SelectedIndexChanged"
                        AutoPostBack="true" />
                </asp:TableCell><asp:TableCell Text="Version:" SkinID="label" />

                <asp:TableCell SkinID="data">
                    <asp:UpdatePanel ID="updVersion" runat="server" ChildrenAsTriggers="false" UpdateMode="Conditional">
                        <ContentTemplate>
                            <asp:DropDownList ID="ddlVersion" runat="server" DataValueField="APV_ID" DataTextField="APV_VALUE"
                                Enabled="false" />
                        </ContentTemplate>
                        <Triggers>
                            <asp:AsyncPostBackTrigger ControlID="ddlApplication" EventName="SelectedIndexChanged" />
                        </Triggers>
                    </asp:UpdatePanel>
                </asp:TableCell><asp:TableCell>
                    <asp:Button ID="btnGoReport" runat="server" Text="Show report" OnClick="btnGoReport_Click" CausesValidation="true" />
                </asp:TableCell><asp:TableCell ColumnSpan="3" />

            </asp:TableRow>
        </asp:Table>
    </div>
    <div>
        <rsweb:ReportViewer ID="report" runat="server" Font-Names="Verdana" Font-Size="8pt"
            InteractiveDeviceInfos="(Collection)" WaitMessageFont-Names="Verdana" WaitMessageFont-Size="14pt"
            Width="100%" Visible="false">
            <LocalReport ReportPath="reports\LogHistory.rdlc" />
        </rsweb:ReportViewer>
    </div>
    </form>
</body>
</html>
