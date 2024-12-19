# Define the full paths to each binary
BINARIES = projet3/src/projet3 \
           project4/src/project4 \
           projetcsoulayma/src/projetcsoulayma \
           salmaproj/src/sallouch 

# Default target
all: run_all

# Rule to run all binaries concurrently
run_all:
	@echo "Launching all binaries..."
	$(foreach binary,$(BINARIES), \
		$(binary) & \
	)
	@echo "All binaries are running in the background."

# Rule to clean up (optional)
clean:
	@echo "No build artifacts to clean."

# Phony targets
.PHONY: all run_all clean

