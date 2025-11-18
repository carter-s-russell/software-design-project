GITBINARY := git
PINGURL := google.com
LIBRARYREPO := simulator_libraries

# --- ADD THIS LINE ---
# Paste the full 40-character commit hash you want to use here.
# I'm using the one from your last 'git log' as an example.
LIBRARY_COMMIT_HASH := 2c225814e1b7d40ffd4f55da92164d1c7717f528
# ---------------------

ifeq ($(OS),Windows_NT)	
	SHELL := CMD
endif

all: update

update:
ifeq ($(OS),Windows_NT)	
# check for internet connection
# if there's internet, check to see if Libraries folder exists
# if it does, remove it before cloning the repo
	@ping -n 1 -w 1000 $(PINGURL) > NUL & \
	if errorlevel 1 \
	( \
		( echo Warning: No internet connection! ) \
	) \
	else \
	( \
		( if exist "$(LIBRARYREPO)" \
		( \
			cd $(LIBRARYREPO) && \
			$(GITBINARY) fetch origin && \
			$(GITBINARY) checkout $(LIBRARY_COMMIT_HASH) && \
			cd .. \
		) \
		else \
		( \
			$(GITBINARY) config --global http.sslVerify false  && \
			$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(LIBRARYREPO).git && \
			cd $(LIBRARYREPO) && \
			$(GITBINARY) checkout $(LIBRARY_COMMIT_HASH) && \
			cd .. \
		) \
		) \
	) 
else
# Mac/Linux
	@ping -c 1 -W 1000 $(PINGURL) > /dev/null ; \
	if [ "$$?" -ne 0 ]; then \
		echo Warning: No internet connection!; \
	else \
		if [ -d "$(LIBRARYREPO)" ]; then \
			cd $(LIBRARYREPO) ; \
			$(GITBINARY) fetch origin ; \
      		$(GITBINARY) checkout $(LIBRARY_COMMIT_HASH) ; \
      		cd .. ; \
		else \
      		$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(LIBRARYREPO).git ; \
			cd $(LIBRARYREPO) ; \
			$(GITBINARY) checkout $(LIBRARY_COMMIT_HASH) ; \
			cd .. ; \
		fi \
	fi \

endif

clean:
	@echo "Clean is handled by your 'build' directory. Run 'rm -rf build' to clean."
