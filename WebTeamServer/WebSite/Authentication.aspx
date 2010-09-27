<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true"
    CodeBehind="Authentication.aspx.cs" Inherits="WebLogging.Authentication" %>

<%@ MasterType VirtualPath="~/MasterPage.Master" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <asp:Label ID="lblBadLogin" runat="server" Text="Invalid Credentials" ForeColor="Red" Visible="false" />
    <br />
    <asp:Label runat="server" Text="Login:" />
    <asp:TextBox ID="tbxLogin" runat="server" />
    <br />
    <asp:Label runat="server" Text="Password" />
    <asp:TextBox ID="tbxPassword" runat="server" TextMode="Password" />
    <br />
    <asp:Button ID="btnLogin" runat="server" OnClick="btnLogin_onClick" Text="Login" />
</asp:Content>
