
AutoNotepadps.dll: dlldata.obj AutoNotepad_p.obj AutoNotepad_i.obj
	link /dll /out:AutoNotepadps.dll /def:AutoNotepadps.def /entry:DllMain dlldata.obj AutoNotepad_p.obj AutoNotepad_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del AutoNotepadps.dll
	@del AutoNotepadps.lib
	@del AutoNotepadps.exp
	@del dlldata.obj
	@del AutoNotepad_p.obj
	@del AutoNotepad_i.obj
