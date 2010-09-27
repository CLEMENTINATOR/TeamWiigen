<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true"
    CodeBehind="Viewer.aspx.cs" Inherits="WebLogging.Viewer" %>

<%@ MasterType VirtualPath="~/MasterPage.Master" %>

<%@ Register Assembly="Microsoft.ReportViewer.WebForms, Version=10.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
    Namespace="Microsoft.Reporting.WebForms" TagPrefix="rsweb" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div>
        <asp:Label runat="server" Text="Start date:" />
        <asp:CustomValidator ID="cvlStartDate" runat="server" Text="!" Display="Dynamic"
            ControlToValidate="tbxStartDate" ValidateEmptyText="false" OnServerValidate="ValidateDate" />
        <asp:TextBox ID="tbxStartDate" runat="server" />&nbsp;
        <asp:ImageButton ID="imgStartDate" runat="server" ImageUrl="~/img/calendar.png" />
        <ajax:CalendarExtender ID="calStartDate" runat="server" TargetControlID="tbxStartDate"
            PopupButtonID="imgStartDate" ClearTime="true" />
        <ajax:MaskedEditExtender ID="meeStartDate" runat="server" TargetControlID="tbxStartDate"
            Mask="99/99/9999" MaskType="Date" />
        <asp:Label runat="server" Text="End date:" />
        <asp:CustomValidator ID="cvlEndDate" runat="server" Text="!" Display="Dynamic" ControlToValidate="tbxEndDate"
            ValidateEmptyText="false" OnServerValidate="ValidateDate" />
        <asp:TextBox ID="tbxEndDate" runat="server" />&nbsp;
        <asp:ImageButton ID="imgEndDate" runat="server" ImageUrl="~/img/calendar.png" />
        <ajax:CalendarExtender ID="calEndDate" runat="server" TargetControlID="tbxEndDate"
            PopupButtonID="imgEndDate" ClearTime="true" />
        <ajax:MaskedEditExtender ID="meeEndDate" runat="server" TargetControlID="tbxEndDate"
            Mask="99/99/9999" MaskType="Date" />
        <br />
        <asp:Label ID="Label1" runat="server" Text="Log type:" />
        <asp:DropDownList ID="ddlLogType" runat="server" DataTextField="LTY_VALUE" DataValueField="LTY_ID"
            OnInit="ddlLogType_Init" />
        <asp:Label runat="server" Text="IP filter:" />
        <asp:TextBox ID="tbxIP" runat="server" MaxLength="15" />
        <br />
        <asp:Label runat="server" Text="Application:" />
        <asp:DropDownList ID="ddlApplication" runat="server" DataValueField="APP_ID" DataTextField="APP_NAME"
            OnInit="ddlApplication_Init" OnSelectedIndexChanged="ddlApplication_SelectedIndexChanged"
            AutoPostBack="true" />
        <asp:Label runat="server" Text="Version:" />
        <asp:UpdatePanel ID="updVersion" runat="server" ChildrenAsTriggers="false" UpdateMode="Conditional" RenderMode="Inline">
            <ContentTemplate>
                <asp:DropDownList ID="ddlVersion" runat="server" DataValueField="APV_ID" DataTextField="APV_VALUE"
                    Enabled="false" />
            </ContentTemplate>
            <Triggers>
                <asp:AsyncPostBackTrigger ControlID="ddlApplication" EventName="SelectedIndexChanged" />
            </Triggers>
        </asp:UpdatePanel>
        <br />
        <asp:Button ID="btnGoReport" runat="server" Text="Show report" OnClick="btnGoReport_Click"
            CausesValidation="true" />
    </div>
    <div>
        <rsweb:ReportViewer ID="report" runat="server" Font-Names="Verdana" Font-Size="8pt"
            InteractiveDeviceInfos="(Collection)" WaitMessageFont-Names="Verdana" WaitMessageFont-Size="14pt"
            Width="100%" Visible="false">
            <LocalReport ReportPath="reports\LogHistory.rdlc" />
        </rsweb:ReportViewer>
    </div>
    <br />
    <asp:Button ID="btnCleanLog" runat="server" Text="Clean logs" OnClick="btnCleanLogs_Click" />
</asp:Content>
