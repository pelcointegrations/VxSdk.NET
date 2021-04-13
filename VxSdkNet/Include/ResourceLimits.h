// Declares the Limits class.
#ifndef ResourceLimits_h__
#define ResourceLimits_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ResourceLimits class represents a map of limits related to a resource. A resource will supply a limit for any
    /// field that is supported but does not have a valid value available. The presence of a limit indicates that
    /// the associated field is supported, regardless of whether the field is present in the resource
    /// representation or not.
    /// </summary>
    public ref class ResourceLimits {
    public:

        /// <summary>
        /// The BooleanLimit class represents the valid values for a boolean field.
        /// </summary>
        ref class BooleanLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="booleanLimit">The boolean limit.</param>
            BooleanLimit(VxSdk::VxLimits::Boolean booleanLimit)
            {
                DefaultValue = booleanLimit.defaultValue;
                FieldName = VxSdkNet::Utils::ConvertCppString(booleanLimit.fieldName);
                HasDefaultValue = booleanLimit.hasDefaultValue;
                Options = gcnew System::Collections::Generic::List<bool>();
                for (int i = 0; i < booleanLimit.optionsSize; ++i)
                {
                    Options->Add(booleanLimit.options[i]);
                }
            }

            /// <summary>
            /// Gets the field’s default value.
            /// </summary>
            /// <value>The default value.</value>
            property bool DefaultValue;

            /// <summary>
            /// Gets the name of the field that this boolean limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets or sets whether <see cref="DefaultValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="DefaultValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasDefaultValue;

            /// <summary>
            /// Gets a list of valid values that may be applied to the field.
            /// <remarks>
            /// If no values are present, this indicates that the field is currently read-only.
            /// </remarks>
            /// </summary>
            /// <value>A list of valid values.</value>
            property System::Collections::Generic::List<bool>^ Options;
        };

        /// <summary>
        /// The Float class represents the valid values for a numeric float field.
        /// </summary>
        ref class FloatLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="floatLimit">The float limit.</param>
            FloatLimit(VxSdk::VxLimits::Float floatLimit)
            {
                DefaultValue = floatLimit.defaultValue;
                FieldName = Utils::ConvertCppString(floatLimit.fieldName);
                HasDefaultValue = floatLimit.hasDefaultValue;
                HasMaxValue = floatLimit.hasMax;
                HasMinValue = floatLimit.hasMin;
                MaxValue = floatLimit.max;
                MinValue = floatLimit.min;
                Options = gcnew System::Collections::Generic::List<float>();
                for (int i = 0; i < floatLimit.optionsSize; ++i)
                {
                    Options->Add(floatLimit.options[i]);
                }
            }

            /// <summary>
            /// Gets the field’s default value.
            /// </summary>
            /// <value>The default value.</value>
            property float DefaultValue;

            /// <summary>
            /// Gets the name of the field that this float limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets or sets whether <see cref="DefaultValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="DefaultValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasDefaultValue;

            /// <summary>
            /// Gets or sets whether <see cref="MaxValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MaxValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMaxValue;

            /// <summary>
            /// Gets or sets whether <see cref="MinValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MinValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMinValue;

            /// <summary>
            /// Gets the field’s maximum valid value.
            /// </summary>
            /// <value>The field’s maximum valid value.</value>
            property float MaxValue;

            /// <summary>
            /// Gets the field’s minimum valid value.
            /// </summary>
            /// <value>The field’s minimum valid value.</value>
            property float MinValue;

            /// <summary>
            /// Gets a list of valid values that may be applied to the field.
            /// <remarks>
            /// If no values are present, this indicates that the field is currently read-only.
            /// </remarks>
            /// </summary>
            /// <value>A list of valid values.</value>
            property System::Collections::Generic::List<float>^ Options;
        };

        /// <summary>
        /// The Integer class represents the valid values for a numeric integer field.
        /// </summary>
        ref class IntegerLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="integerLimit">The integer limit.</param>
            IntegerLimit(VxSdk::VxLimits::Integer integerLimit)
            {
                DefaultValue = integerLimit.defaultValue;
                FieldName = Utils::ConvertCppString(integerLimit.fieldName);
                HasDefaultValue = integerLimit.hasDefaultValue;
                HasMaxValue = integerLimit.hasMax;
                HasMinValue = integerLimit.hasMin;
                MaxValue = integerLimit.max;
                MinValue = integerLimit.min;
            }

            /// <summary>
            /// Gets the field’s default value.
            /// </summary>
            /// <value>The default value.</value>
            property int DefaultValue;

            /// <summary>
            /// Gets the name of the field that this integer limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets or sets whether <see cref="DefaultValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="DefaultValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasDefaultValue;

            /// <summary>
            /// Gets or sets whether <see cref="MaxValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MaxValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMaxValue;

            /// <summary>
            /// Gets or sets whether <see cref="MinValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MinValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMinValue;

            /// <summary>
            /// Gets the field’s maximum valid value.
            /// </summary>
            /// <value>The field’s maximum valid value.</value>
            property int MaxValue;

            /// <summary>
            /// Gets the field’s minimum valid value.
            /// </summary>
            /// <value>The field’s minimum valid value.</value>
            property int MinValue;
        };

        /// <summary>
        /// The List class represents the valid values for an array field.
        /// </summary>
        ref class ListLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="listLimit">The list limit.</param>
            ListLimit(VxSdk::VxLimits::List listLimit)
            {
                FieldName = Utils::ConvertCppString(listLimit.fieldName);
                HasMaxItems = listLimit.hasMaxItems;
                HasMinItems = listLimit.hasMinItems;
                MaxItems = listLimit.maxItems;
                MinItems = listLimit.minItems;
            }

            /// <summary>
            /// Gets the name of the field that this list limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets or sets whether <see cref="MaxItems"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MaxItems"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMaxItems;

            /// <summary>
            /// Gets or sets whether <see cref="MinItems"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="MinItems"/> has been set, otherwise <c>false</c>.</value>
            property bool HasMinItems;

            /// <summary>
            /// Gets the maximum number of items that may appear in the list.
            /// </summary>
            /// <value>The maximum number of items.</value>
            property int MaxItems;

            /// <summary>
            /// Gets the minimum number of items that may appear in the list.
            /// </summary>
            /// <value>The minimum number of items.</value>
            property int MinItems;
        };

        /// <summary>
        /// The Object class represents the valid values for an object field.
        /// </summary>
        ref class ObjectLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="objectLimit">The object limit.</param>
            ObjectLimit(VxSdk::VxLimits::Object objectLimit)
            {
                FieldName = Utils::ConvertCppString(objectLimit.fieldName);
                Options = gcnew System::Collections::Generic::List<System::String^>();
                for (int i = 0; i < objectLimit.optionsSize; ++i)
                {
                    Options->Add(Utils::ConvertCppString(objectLimit.options[i]));
                }
            }

            /// <summary>
            /// Gets the name of the field that this object limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets a list of valid values that may be applied to the field.
            /// <remarks>
            /// If no values are present, this indicates that the field is currently read-only.
            /// </remarks>
            /// </summary>
            /// <value>A list of valid values.</value>
            property System::Collections::Generic::List<System::String^>^ Options;
        };

        /// <summary>
        /// The String class represents the valid values for a string field.
        /// </summary>
        ref class StringLimit {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="stringLimit">The string limit.</param>
            StringLimit(VxSdk::VxLimits::String stringLimit)
            {
                DefaultValue = Utils::ConvertCppString(stringLimit.defaultValue);
                FieldName = Utils::ConvertCppString(stringLimit.fieldName);
                HasDefaultValue = stringLimit.hasDefaultValue;
                Options = gcnew System::Collections::Generic::List<System::String^>();
                for (int i = 0; i < stringLimit.optionsSize; ++i)
                {
                    Options->Add(Utils::ConvertCppString(stringLimit.options[i]));
                }
            }

            /// <summary>
            /// Gets the field’s default value.
            /// </summary>
            /// <value>The default value.</value>
            property System::String^ DefaultValue;

            /// <summary>
            /// Gets the name of the field that this string limit applies to.
            /// </summary>
            /// <value>The field name.</value>
            property System::String^ FieldName;

            /// <summary>
            /// Gets or sets whether <see cref="DefaultValue"/> has been set
            /// </summary>
            /// <value><c>true</c> if <see cref="DefaultValue"/> has been set, otherwise <c>false</c>.</value>
            property bool HasDefaultValue;

            /// <summary>
            /// Gets a list of valid values that may be applied to the field.
            /// <remarks>
            /// If no values are present, this indicates that the field is currently read-only.
            /// </remarks>
            /// </summary>
            /// <value>A list of valid values.</value>
            property System::Collections::Generic::List<System::String^>^ Options;
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLimits">The vx limits.</param>
        ResourceLimits(VxSdk::VxLimits* vxLimits)
        {
            _limits = vxLimits;
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~ResourceLimits() {
            this->!ResourceLimits();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !ResourceLimits() {
            _limits->Clear();
            _limits = nullptr;
        }

        /// <summary>
        /// Gets the boolean limits.
        /// </summary>
        /// <value>A <c>List</c> of boolean limits, if any.</value>
        property System::Collections::Generic::List<BooleanLimit^>^ BooleanLimits {
        public:
            System::Collections::Generic::List<BooleanLimit^>^ get() {
                System::Collections::Generic::List<BooleanLimit^>^ mlist = gcnew System::Collections::Generic::List<BooleanLimit^>();
                for (int i = 0; i < _limits->booleanLimitsSize; i++)
                    mlist->Add(gcnew BooleanLimit(_limits->booleanLimits[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the float limits.
        /// </summary>
        /// <value>A <c>List</c> of float limits, if any.</value>
        property System::Collections::Generic::List<FloatLimit^>^ FloatLimits {
        public:
            System::Collections::Generic::List<FloatLimit^>^ get() {
                System::Collections::Generic::List<FloatLimit^>^ mlist = gcnew System::Collections::Generic::List<FloatLimit^>();
                for (int i = 0; i < _limits->floatLimitsSize; i++)
                    mlist->Add(gcnew FloatLimit(_limits->floatLimits[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the integer limits.
        /// </summary>
        /// <value>A <c>List</c> of integer limits, if any.</value>
        property System::Collections::Generic::List<IntegerLimit^>^ IntegerLimits {
        public:
            System::Collections::Generic::List<IntegerLimit^>^ get() {
                System::Collections::Generic::List<IntegerLimit^>^ mlist = gcnew System::Collections::Generic::List<IntegerLimit^>();
                for (int i = 0; i < _limits->integerLimitsSize; i++)
                    mlist->Add(gcnew IntegerLimit(_limits->integerLimits[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the list limits.
        /// </summary>
        /// <value>A <c>List</c> of list limits, if any.</value>
        property System::Collections::Generic::List<ListLimit^>^ ListLimits {
        public:
            System::Collections::Generic::List<ListLimit^>^ get() {
                System::Collections::Generic::List<ListLimit^>^ mlist = gcnew System::Collections::Generic::List<ListLimit^>();
                for (int i = 0; i < _limits->listLimitsSize; i++)
                    mlist->Add(gcnew ListLimit(_limits->listLimits[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the object limits.
        /// </summary>
        /// <value>A <c>List</c> of object limits, if any.</value>
        property System::Collections::Generic::List<ObjectLimit^>^ ObjectLimits {
        public:
            System::Collections::Generic::List<ObjectLimit^>^ get() {
                System::Collections::Generic::List<ObjectLimit^>^ mlist = gcnew System::Collections::Generic::List<ObjectLimit^>();
                for (int i = 0; i < _limits->objectLimitsSize; i++)
                    mlist->Add(gcnew ObjectLimit(_limits->objectLimits[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the string limits.
        /// </summary>
        /// <value>A <c>List</c> of string limits, if any.</value>
        property System::Collections::Generic::List<StringLimit^>^ StringLimits {
        public:
            System::Collections::Generic::List<StringLimit^>^ get() {
                System::Collections::Generic::List<StringLimit^>^ mlist = gcnew System::Collections::Generic::List<StringLimit^>();
                for (int i = 0; i < _limits->stringLimitsSize; i++)
                    mlist->Add(gcnew StringLimit(_limits->stringLimits[i]));

                return mlist;
            }
        }


        internal:
            VxSdk::VxLimits* _limits;
    };
}
#endif // ResourceLimits_h__
