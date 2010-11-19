#ifndef _GTHEME_DDL_H_
#define _GTHEME_DDL_H_

#include <Libwui/Component/DropDownList.hpp>

class GThemeDdl : public Libwui::Component::DropDownList
{
public:
	void InitializeComponents();
	
protected:
	void OnSelectedItemChanged(Libwui::Device::PadController &c);
};

#endif