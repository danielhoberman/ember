.PHONY: test-all cpp-tests py-tests install-dev

install-dev:
	uv pip install -e .

cpp-tests:
	./cpp_tests/build/unit_tests

py-tests:
	uv run pytest

test-all: install-dev py-tests cpp-tests
