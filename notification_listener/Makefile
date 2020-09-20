.PHONY: install
install:
	@virtualenv -p python3 env \
	&& . env/bin/activate \
	&& pip install -r requirements.txt

.PHONY: run
run:
	@source env/bin/activate && python listen.py
