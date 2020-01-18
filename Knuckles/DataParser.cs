using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Knuckles
{
	class DataParser
	{
		String RadioParser(String input)
		{
			char CommandType = input.ElementAt(0);
			
			//already in the format we want it
			if(CommandType.Equals('G') || CommandType.Equals('B'))
			{
				return input;
			}
			return "";
		}
	}
}
