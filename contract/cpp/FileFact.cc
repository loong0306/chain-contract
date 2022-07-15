#include "chainmaker/chainmaker.h"
using namespace chainmaker;
class Counter : public Contract
{
public:
    void init_contract() {}
    void upgrade() {}

    void save()
    {
        Context *ctx = context();

        std::string file_hash;
        std::string file_name;
        std::string tx_id;

        ctx->arg("file_hash", file_hash);
        ctx->arg("file_name", file_name);
        ctx->emit_event("topic_vx",2,file_hash, file_name.c_str());
        ctx->arg("tx_id", tx_id);
        ctx->log("call save() tx_id:" + tx_id);
        ctx->log("call save() file_hash:" + file_hash);
        ctx->log("call save() file_name:" + file_name);
        std::string test_str = tx_id + " " + file_name + " " + file_hash;
        ctx->put_object(file_hash, test_str);
        ctx->log("put success:" + test_str);
        ctx->success(test_str);
    }

    void find_by_file_hash()
    {
        Context *ctx = context();
        std::string file_hash;
        ctx->arg("file_hash", file_hash);
        std::string value;
        ctx->get_object(file_hash, &value);
        ctx->log(value);
        auto *value_items = easy_unmarshal((byte *)value.data());
        std::string value_str = value_items->get_value("value");
        ctx->log("result: " + value_str);
        ctx->success(value_str);
        delete (value_items);
    }

    void functional_verify()
    {
        Context *ctx = context();
        std::string value;
        std::string value_str;
        ctx->log("===================================functionTest start===================================");
        ctx->get_object("test", &value);
        auto *value_items = easy_unmarshal((byte *)value.data());
        value_str = value_items->get_value("value");
        ctx->log("result: " + value_str);

        ctx->put_object("test", "test");
        ctx->get_object("test", &value);
        value_items = easy_unmarshal((byte *)value.data());
        value_str = value_items->get_value("value");
        ctx->log("result: " + value_str);

        ctx->delete_object("test");
        ctx->get_object("test", &value);
        value_items = easy_unmarshal((byte *)value.data());
        value_str = value_items->get_value("value");
        ctx->log("result: " + value_str);
        delete (value_items);
        {
            auto *parameters = new EasyCodecItems(1);
            std::string resp;
            std::string param_value = "test";
            parameters->ecitems[0].key = (char *)"file_hash";
            parameters->ecitems[0].key_type = easy_key_type_user;
            parameters->ecitems[0].value_type = easy_value_type_string;
            parameters->ecitems[0].value = (char *)param_value.data();
            ctx->call("contract01", "save", parameters, &resp);
            auto *call_items = easy_unmarshal((byte *)resp.data());
            std::string result;
            result = call_items->get_value("result");
            ctx->log("[call save] result: [" + result + "]");
        }
        {
            auto *parameters = new EasyCodecItems(1);
            std::string param_value = "test";
            parameters->ecitems[0].key = (char *)"file_hash";
            parameters->ecitems[0].key_type = easy_key_type_user;
            parameters->ecitems[0].value_type = easy_value_type_string;
            parameters->ecitems[0].value = (char *)param_value.data();
            std::string resp;
            ctx->call("contract01", "find_by_file_hash", parameters, &resp);
            auto *call_items = easy_unmarshal((byte *)resp.data());
            std::string result;
            int32_t code = -1;
            string strCode = call_items->get_value("code");
            memcpy(&code, &strCode[0], sizeof(code));
            if (code == SUCCESS)
            {
                result = call_items->get_value("result");
                ctx->log("[call find_by_file_hash] result: [" + result + "]");
            }
            else
            {
                ctx->log("failed call find_by_file_hash");
            }
            delete (parameters);
            delete (call_items);
        }
    }
};

// 在创建本合约时, 调用一次init方法. ChainMaker不允许用户直接调用该方法.
WASM_EXPORT void init_contract()
{
    Counter counter;
    counter.init_contract();
}

// 在升级本合约时, 对于每一个升级的版本调用一次upgrade方法. ChainMaker不允许用户直接调用该方法.
WASM_EXPORT void upgrade()
{
    Counter counter;
    counter.init_contract();
}

WASM_EXPORT void functional_verify()
{
    Counter counter;
    counter.functional_verify();
}
WASM_EXPORT void save()
{
    Counter counter;
    counter.save();
}

WASM_EXPORT void find_by_file_hash()
{
    Counter counter;
    counter.find_by_file_hash();
}