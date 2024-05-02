// Copyright 2013-2024 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSONSCHEMA_JSON_SCHEMA_HPP
#define JSONCONS_JSONSCHEMA_JSON_SCHEMA_HPP

#include <jsoncons/config/jsoncons_config.hpp>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <jsoncons_ext/jsonschema/jsonschema_error.hpp>
#include <jsoncons_ext/jsonschema/common/schema_validators.hpp>

namespace jsoncons {
namespace jsonschema {

    class throwing_error_listener : public error_listener
    {
        void do_error(const validation_message& msg) override
        {
            JSONCONS_THROW(validation_error(msg.instance_location().string() + ": " + msg.message()));
        }
    };

    class fail_early_listener : public error_listener
    {
        void do_error(const validation_message&) override
        {
        }
    public:
        fail_early_listener()
            : error_listener(true)
        {
        }
    };

    using error_reporter_t = std::function<void(const validation_message& msg)>;

    struct error_reporter_adaptor : public error_listener
    {
        error_reporter_t reporter_;

        error_reporter_adaptor(const error_reporter_t& reporter)
            : reporter_(reporter)
        {
        }
    private:
        void do_error(const validation_message& e) override
        {
            reporter_(e);
        }
    };
       
    template <class Json>
    class json_validator;
    
    template <class Json>
    class json_schema
    {
        using keyword_validator_type = std::unique_ptr<keyword_validator<Json>>;
        using document_schema_validator_type = std::unique_ptr<document_schema_validator<Json>>;

        document_schema_validator_type root_;
        
        friend class json_validator<Json>;
    public:
        json_schema(document_schema_validator_type&& root)
            : root_(std::move(root))
        {
            if (root_ == nullptr)
                JSONCONS_THROW(schema_error("There is no root schema to validate an instance against"));
        }

        json_schema(const json_schema&) = delete;
        json_schema(json_schema&&) = default;
        json_schema& operator=(const json_schema&) = delete;
        json_schema& operator=(json_schema&&) = default;

        // Validate input JSON against a JSON Schema with a default throwing error reporter
        Json validate(const Json& instance) const
        {
            throwing_error_listener reporter;
            jsonpointer::json_pointer instance_location{};
            Json patch(json_array_arg);

            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, reporter, patch);
            return patch;
        }

        // Validate input JSON against a JSON Schema 
        bool is_valid(const Json& instance) const
        {
            fail_early_listener reporter;
            jsonpointer::json_pointer instance_location{};
            Json patch(json_array_arg);

            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, reporter, patch);
            return reporter.error_count() == 0;
        }

        // Validate input JSON against a JSON Schema with a provided error reporter
        template <class MsgReporter>
        typename std::enable_if<extension_traits::is_unary_function_object_exact<MsgReporter,walk_result,validation_message>::value,void>::type
        validate(const Json& instance, const MsgReporter& reporter) const
        {
            jsonpointer::json_pointer instance_location{};
            Json patch(json_array_arg);

            error_reporter_adaptor adaptor(reporter);
            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, adaptor, patch);
        }

        // Validate input JSON against a JSON Schema with a provided error reporter
        template <class MsgReporter>
        typename std::enable_if<extension_traits::is_unary_function_object_exact<MsgReporter,walk_result,validation_message>::value,void>::type
        validate(const Json& instance, MsgReporter&& reporter, Json& patch) const
        {
            jsonpointer::json_pointer instance_location{};
            patch = Json(json_array_arg);

            error_reporter_adaptor adaptor(std::forward<MsgReporter>(reporter));
            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, adaptor, patch);
        }

        // Validate input JSON against a JSON Schema with a provided error reporter
        void validate(const Json& instance, Json& patch) const
        {
            jsonpointer::json_pointer instance_location{};
            patch = Json(json_array_arg);

            fail_early_listener reporter;
            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, reporter, patch);
        }

        // Validate input JSON against a JSON Schema with a provided json_visitor
        void validate(const Json& instance, json_visitor& visitor) const
        {
            visitor.begin_array();
            jsonpointer::json_pointer instance_location{};
            Json patch{json_array_arg};

            validation_message_to_json_adaptor report{ visitor };
            evaluation_context<Json> context;
            evaluation_results results;
            error_reporter_adaptor adaptor(report);
            root_->validate(context, instance, instance_location, results, adaptor, patch);
            visitor.end_array();
            visitor.flush();
        }
        
        template <class WalkReporter>
        void walk(const Json& instance, const WalkReporter& reporter) const
        {
            jsonpointer::json_pointer instance_location{};

            root_->walk(evaluation_context<Json>{}, instance, instance_location, reporter);
        }
        
    private:
        // Validate input JSON against a JSON Schema with a provided error reporter
        void validate2(const Json& instance, error_listener& reporter, Json& patch) const
        {
            jsonpointer::json_pointer instance_location{};
            patch = Json(json_array_arg);

            evaluation_context<Json> context;
            evaluation_results results;
            root_->validate(context, instance, instance_location, results, reporter, patch);
        }
    };


} // namespace jsonschema
} // namespace jsoncons

#endif // JSONCONS_JSONSCHEMA_SCHEMA_HPP
