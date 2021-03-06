﻿-- =============================================
-- Author:		Morelle Julien
-- Create date: 10/08/2010
-- Description:	Create new log session.
-- =============================================


CREATE PROCEDURE [dbo].[START_SESSION]
	@APP_NAME as nvarchar(50),
	@APV_VALUE as nvarchar(10),
	@STA_USER_IP as varchar(15)
AS
	SET NOCOUNT ON

	DECLARE @APP_ID AS INT
	DECLARE @APV_ID AS INT

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
		

	IF NOT EXISTS(SELECT TOP(1) 1 FROM STATS 
					WHERE @APV_ID = STA_APV_ID
						AND @STA_USER_IP = STA_USER_IP)
	BEGIN
		DELETE LOG
			WHERE LOG_APV_ID = @APV_ID
			AND	  LOG_USER_IP = @STA_USER_IP

		INSERT INTO STATS(STA_APV_ID, STA_NB_USE, STA_USER_IP, STA_LAST_USE)
			VALUES(@APV_ID, 1, @STA_USER_IP, GETDATE())
	END
	ELSE
		UPDATE STATS
			SET STA_NB_USE = STA_NB_USE + 1,
				STA_LAST_USE= GETDATE()
			WHERE STA_APV_ID = @APV_ID
				AND STA_USER_IP = @STA_USER_IP

	SET NOCOUNT OFF
RETURN 0