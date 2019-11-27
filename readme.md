
# Steps to Reproduce the Issue.

Build the Solution with Visual Studio in Administrator Mode so that the C++ Com Dll can be registered at build completion.

The Test project uses the Clear Script 5.6.0 nuget package.

Run the Console Test application from the debugger and you will see that a exception is returned around GetEnumerator.

The exception will be as follows:

```code
Exception: Microsoft.ClearScript.ScriptEngineException: The best overloaded method match for 'Microsoft.ClearScript.Util.EnumerableHelpers.GetEnumerator(System.Collections.IEnumerable)' has some invalid arguments ---> System.Runtime.InteropServices.COMException: The best overloaded method match for 'Microsoft.ClearScript.Util.EnumerableHelpers.GetEnumerator(System.Collections.IEnumerable)' has some invalid arguments
   at Microsoft.ClearScript.Windows.WindowsScriptEngine.ThrowHostException(Exception exception)
   at Microsoft.ClearScript.Windows.WindowsScriptEngine.HostInvoke[T](Func`1 func)
   at Microsoft.ClearScript.HostItem.HostInvoke[T](Func`1 func)
   at Microsoft.ClearScript.HostItem.InvokeReflectMember(String name, BindingFlags invokeFlags, Object[] wrappedArgs, CultureInfo culture, String[] namedParams, Boolean& isCacheable)
   at Microsoft.ClearScript.HostItem.System.Reflection.IReflect.InvokeMember(String name, BindingFlags invokeFlags, Binder binder, Object invokeTarget, Object[] wrappedArgs, ParameterModifier[] modifiers, CultureInfo culture, String[] namedParams)
   at Microsoft.ClearScript.HostItem.Microsoft.ClearScript.Util.IDynamic.InvokeMethod(String name, Object[] args)
   at Microsoft.ClearScript.HostItem.InvokeHostMember(String name, BindingFlags invokeFlags, Object[] args, Object[] bindArgs, CultureInfo culture, Boolean& isCacheable)
   at Microsoft.ClearScript.HostItem.InvokeMember(String name, BindingFlags invokeFlags, Object[] args, Object[] bindArgs, CultureInfo culture, Boolean bypassTunneling, Boolean& isCacheable)
   at Microsoft.ClearScript.HostItem.<>c__DisplayClass156_0.<InvokeReflectMember>b__0()
   at Microsoft.ClearScript.ScriptEngine.HostInvoke[T](Func`1 func)
   at Microsoft.ClearScript.Windows.WindowsScriptEngine.HostInvoke[T](Func`1 func)
   --- End of inner exception stack trace ---
   at Microsoft.ClearScript.Windows.WindowsScriptItem.TryBindAndInvoke(DynamicMetaObjectBinder binder, Object[] args, Object& result)
   at Microsoft.ClearScript.ScriptItem.<>c__DisplayClass7_0.<TryWrappedBindAndInvoke>b__0()
   at Microsoft.ClearScript.Windows.WindowsScriptEngine.<>c__DisplayClass57_0`1.<ScriptInvoke>b__0()
   at Microsoft.ClearScript.ScriptEngine.ScriptInvokeInternal[T](Func`1 func)
   at Microsoft.ClearScript.ScriptEngine.ScriptInvoke[T](Func`1 func)
   at Microsoft.ClearScript.Windows.WindowsScriptEngine.ScriptInvoke[T](Func`1 func)
   at Microsoft.ClearScript.ScriptItem.TryWrappedBindAndInvoke(DynamicMetaObjectBinder binder, Object[] wrappedArgs, Object& result)
   at Microsoft.ClearScript.ScriptItem.TryWrappedInvokeOrInvokeMember(DynamicMetaObjectBinder binder, ParameterInfo[] parameters, Object[] args, Object& result)
   at Microsoft.ClearScript.ScriptItem.TryInvokeMember(InvokeMemberBinder binder, Object[] args, Object& result)
   at CallSite.Target(Closure , CallSite , Object )
   at System.Dynamic.UpdateDelegates.UpdateAndExecute1[T0,TRet](CallSite site, T0 arg0)
   at ClearScriptTester.Program.Main(String[] args) in C:\_Dev\Sunlife\Cwi.NoShow.Helper\Cwi.NoShow.Helper\ClearScriptTester\Program.cs:line 48
   --- Script error details follow ---
   The best overloaded method match for 'Microsoft.ClearScript.Util.EnumerableHelpers.GetEnumerator(System.Collections.IEnumerable)' has some invalid arguments
       at runme (Script:8:0) -> for each item in helperObject.ChildList
```

The issue only occurs if the object that implements the interface IChildList does not have a coclass in the IDL/Typelibrary.

This seems to cause the HostObject to have the Target property as __ComObject and the Type property has the interface IChildList.

If I modify WindowsScriptEngine.cs and add the following fragment to the MarshalToScriptInternal method, then the native object is returned to the script and the script executes fine.

```code
            var hostObject = obj as HostObject;
            if (hostObject != null && hostObject.Target != null)
            {
                if (hostObject.Target.GetType().IsCOMObject)
                {
                    return new DispatchWrapper(hostObject.Target);
                }
            }
```

I understand this is not ideal as there are cases where a interface is not a Dual interface/ IDispatch and you would want to wrap the COMObject.

