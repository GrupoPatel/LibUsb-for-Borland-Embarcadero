//---------------------------------------------------------------------------
#include <stdio.h>

#include "libusb-1.0.h"
#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
int i;
i=0;
}
 void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0, j = 0;
	uint8_t path[8];
	char tec[1000];
	int r;
	struct libusb_device_descriptor desc;
	while ((dev = devs[i++]) != NULL)
		{

		r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0)
			return;


		sprintf(tec,"%04x:%04x (bus %d, device %d)",desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));
		Form5->Memo1->Lines->Add(tec);
		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			sprintf(tec," path: %d", path[0]);
			Form5->Memo1->Lines->Add(tec);
			for (j = 1; j < r; j++)
				{
				sprintf(tec,".%d", path[j]);
				Form5->Memo1->Lines->Add(tec);
				}
                           }
                 }

	}

//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
	libusb_device **devs;
	int r;
	ssize_t cnt;

	r = libusb_init(NULL);
	if (r < 0)
		return ;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0){
		libusb_exit(NULL);
		return;
	}

	print_devs(devs);
	libusb_free_device_list(devs, 1);
	return ;

	}
//---------------------------------------------------------------------------
