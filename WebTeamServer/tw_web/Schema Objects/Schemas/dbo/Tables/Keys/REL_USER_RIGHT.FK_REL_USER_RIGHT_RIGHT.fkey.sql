﻿ALTER TABLE [dbo].[REL_USER_RIGHT]
	ADD CONSTRAINT [FK_REL_USER_RIGHT_RIGHT] 
	FOREIGN KEY (RUR_RIG_ID)
	REFERENCES [dbo].[RIGHT] (RIG_ID)	
