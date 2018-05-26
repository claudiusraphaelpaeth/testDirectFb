/*
 * testDirectFb.c
 * Copyright (C) 2016 Elyes ABEDA <elyes.abeda@gmail.com>
 *
 * testDirectFb is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * testDirectFb is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libLog.h>
#include <directfb.h>

#define MODULE_NAME "testDirectFb"

int main(int agrc, char **argv)
{
	IDirectFB *_iDfb = NULL;
	IDirectFBSurface *_primSurfDfb = NULL;
	DFBResult _resDfb;
	DFBSurfaceDescription _dscDfb;
	IDirectFBImageProvider *_provImgDfb = NULL;

	myLog_init(MODULE_NAME);
	ENTER_FUNCTION();

	_resDfb = DirectFBInit(&agrc, &argv);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "DirectFBInit() error [%s] %m", DirectFBErrorString(_resDfb));
	_resDfb = DirectFBCreate(&_iDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "DirectFBCreate() error [%s] %m", DirectFBErrorString(_resDfb));

	_resDfb = _iDfb->SetCooperativeLevel(_iDfb, DFSCL_FULLSCREEN);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_iDfb->SetCooperativeLevel() error [%s] %m", DirectFBErrorString(_resDfb));

	memset(&_dscDfb, 0, sizeof(DFBSurfaceDescription));
	_dscDfb.flags = DSDESC_CAPS;
	_dscDfb.caps = DSCAPS_PRIMARY;

	_resDfb = _iDfb->CreateSurface(_iDfb, &_dscDfb, &_primSurfDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_iDfb->CreateSurface() error [%s] %m", DirectFBErrorString(_resDfb));

	_resDfb = _iDfb->CreateImageProvider(_iDfb, "test.png", &_provImgDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_iDfb->CreateImageProvider() error [%s] %m", DirectFBErrorString(_resDfb));

	_resDfb = _provImgDfb->RenderTo(_provImgDfb, _primSurfDfb, NULL);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_provImgDfb->RenderTo() error [%s] %m", DirectFBErrorString(_resDfb));

	_resDfb = _provImgDfb->Release(_provImgDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_provImgDfb->Release() error [%s] %m", DirectFBErrorString(_resDfb));

	sleep(5);

	_resDfb = _primSurfDfb->Release(_primSurfDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_primSurfDfb->Release() error [%s] %m", DirectFBErrorString(_resDfb));

	_resDfb = _iDfb->Release(_iDfb);
	RETURN_IF_FAILS(_resDfb, EXIT_FAILURE, "_iDfb->Release() error [%s] %m", DirectFBErrorString(_resDfb));

	LEAVE_FUNCTION();
	myLog_close();

	return EXIT_SUCCESS;
}
