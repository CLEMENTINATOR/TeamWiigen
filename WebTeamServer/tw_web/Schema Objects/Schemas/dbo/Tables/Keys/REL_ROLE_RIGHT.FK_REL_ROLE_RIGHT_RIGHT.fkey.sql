﻿ALTER TABLE [dbo].[REL_ROLE_RIGHT]
	ADD CONSTRAINT [FK_REL_ROLE_RIGHT_RIGHT] 
	FOREIGN KEY (RRR_RIG_ID)
	REFERENCES [dbo].[RIGHT] (RIG_ID)	
