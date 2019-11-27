using Microsoft.ClearScript;
using Microsoft.ClearScript.Windows;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClearScriptTester
{
    class Program
    {
        static void Main(string[] args)
        {
            VBScriptEngine engine = new VBScriptEngine(WindowsScriptEngineFlags.EnableDebugging);

            var helperType = Type.GetTypeFromProgID("CWI.NoShowHelper");
            var helper = Activator.CreateInstance(helperType);

            var container = new GlobalContainerObject(helper);
            engine.AddHostObject("Container", HostItemFlags.GlobalMembers, container);

            string vbscript = $@"
function runme()

dim result
result = 0
dim helperObject
set helperObject = GetHelper()

for each item in helperObject.ChildList

result = result + item.id

next

runme = result

end function

";

            engine.Execute(vbscript);

            try
            {
                Console.WriteLine("Result should be 3 if successful");
                var result = engine.Script.RunMe();
                Console.WriteLine($"The Result was: {Convert.ToInt32(result)}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception: {ex.ToString()}");
            }

            Console.WriteLine("Done, press any key to Exit");
            Console.ReadLine();

        }
    }

    public class GlobalContainerObject
    {
        private object _noShowHelper;
        public GlobalContainerObject(object noShowHelper)
        {
            _noShowHelper = noShowHelper;
        }
        public object GetHelper()
        {
            return _noShowHelper;
        }
    }
}
