VERSION=2.0.0

build:
	- wasm-pack build
	
sql: build 
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-sql-$(VERSION).wasm

sql-perf: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/send_proposal_request_sql/perf/rust-sql-perf-$(VERSION).wasm

fact: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-fact-$(VERSION).wasm

verify: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-fact-$(VERSION).wasm
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-func-verify-$(VERSION).wasm
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-counter-$(VERSION).wasm

asset: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm ../chainmaker-go/test/wasm/rust-asset-$(VERSION).wasm

qc-kv: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm target/wasm32-unknown-unknown/release/rust-qc-kv-$(VERSION).wasm

qc-sql: build
	- cp -f target/wasm32-unknown-unknown/release/chainmaker_contract.wasm target/wasm32-unknown-unknown/release/rust-qc-sql-$(VERSION).wasm