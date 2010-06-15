-- =============================================
-- Author:		Morelle Julien
-- Create date: 10/06/2010
-- Description:	Create an entry in the logs
-- =============================================

CREATE PROCEDURE [dbo].[INS_LOG]
	@APP_NAME as nvarchar(50),
	@APV_VALUE as nvarchar(10),
	@LTY_CODE as nvarchar(3),
	@LOG_MESSAGE as nvarchar(255),
	@LOG_SOURCE as nvarchar(255),
	@LOG_LINE as int,
	@LOG_USER_IP as varchar(15)
AS
BEGIN
	SET NOCOUNT ON;
	
	/* declaration of all needed ids */
	DECLARE @APP_ID as int
	DECLARE @APV_ID as int
	DECLARE @LTY_ID as int
	
	/* Getting error code id */
	IF NOT EXISTS(SELECT TOP(1) 1 FROM LOG_TYPE WHERE LTY_CODE = @LTY_CODE)
		raiserror('LTY_CODE invalid!', 16, 1)
	SELECT @LTY_ID = LTY_ID FROM LOG_TYPE WHERE LTY_CODE = @LTY_CODE
	
	/* Getting application id (create the application if it doesn't exists) */
	IF NOT EXISTS(SELECT TOP(1) 1 FROM APPLICATIONS WHERE APP_NAME = @APP_NAME)
	BEGIN
		INSERT INTO APPLICATIONS(APP_NAME) VALUES(@APP_NAME)
		SELECT @APP_ID = @@IDENTITY
	END
	ELSE
		SELECT @APP_ID = APP_ID FROM APPLICATIONS WHERE APP_NAME = @APP_NAME
	
	/* Getting application version (create the application if it doesn't exists) */
	IF NOT EXISTS(SELECT TOP(1) 1 FROM APPLICATION_VERSION WHERE APV_APP_ID = @APP_ID AND APV_VALUE = @APV_VALUE)
	BEGIN
		INSERT INTO APPLICATION_VERSION(APV_APP_ID, APV_VALUE) VALUES(@APP_ID, @APV_VALUE)
		SELECT @APV_ID = @@IDENTITY
	END
	ELSE
		SELECT @APV_ID = APV_ID FROM APPLICATION_VERSION WHERE APV_APP_ID = @APP_ID AND APV_VALUE = @APV_VALUE
		
	/* Insert the log in the database */
	INSERT INTO LOG(LOG_APV_ID, LOG_LTY_ID, LOG_SOURCE, LOG_LINE, LOG_MESSAGE, LOG_USER_IP)
		VALUES(@APV_ID, @LTY_ID, @LOG_SOURCE, @LOG_LINE, @LOG_MESSAGE, @LOG_USER_IP)
		
	/* return the created log id */
	SELECT @@Identity
END
