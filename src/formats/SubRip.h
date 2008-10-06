#ifndef _SubRip_h
#define _SubRip_h

/*
 *	subtitleeditor -- a tool to create or edit subtitle
 *
 *	http://home.gna.org/subtitleeditor/
 *	https://gna.org/projects/subtitleeditor/
 *
 *	Copyright @ 2005-2008, kitone
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "SubtitleFormat.h"
#include "RegEx.h"


/*
 * format:
 *
 * number
 * start --> end
 * text
 * (empty line)
 */
class SubRip : public SubtitleFormat
{
public:

	/*
	 *
	 */
	static SubtitleFormatInfo get_info()
	{
		SubtitleFormatInfo info;
		info.name = "SubRip";
		info.extension = "srt";

		info.pattern = 
			"\\d\\R"
			"\\d+:\\d+:\\d+,\\d+\\s-->\\s\\d+:\\d+:\\d+,\\d+\\R";
		
		return info;
	}

	/*
	 *
	 */
	void open(FileReader &file)
	{
		RegEx re_num("^\\d+$");
		RegEx re_time("^(\\d+):(\\d+):(\\d+),(\\d+)\\s-->\\s(\\d+):(\\d+):(\\d+),(\\d+)");

		int start[4], end[4];
		Subtitles subtitles = document()->subtitles();

		Glib::ustring line;

		while(file.getline(line))
		{
			// Read the subtitle number (don't needs)
			if(re_num.exec(line))
			{
				file.getline(line); // Next line is a time line

				// Read the subtitle time "start --> end"
				if(re_time.FullMatch(line.c_str(), 
								&start[0], &start[1], &start[2], &start[3], 
								&end[0], &end[1], &end[2], &end[3]))
				{
					Glib::ustring text;
					int count = 0;

					// Read the text lines
					while(file.getline(line) && !line.empty())
					{
						if(count > 0)
							text += '\n';

						text += line;

						++count;
					}
		
					// Append a subtitle
					Subtitle sub = subtitles.append();

					sub.set_text(text);
					sub.set_start_and_end(
								SubtitleTime(start[0], start[1], start[2], start[3]),
								SubtitleTime(end[0], end[1], end[2], end[3]));
				}
			}
		}
	}


	/*
	 *
	 */
	void save(FileWriter &file)
	{
		unsigned int count = 1;
		for(Subtitle sub = document()->subtitles().get_first(); sub; ++sub, ++count)
		{
			file 
				<< count 
				<< std::endl
				<< time_to_subrip(sub.get_start())
				<< " --> "
				<< time_to_subrip(sub.get_end())
				<< std::endl;

			Glib::ustring text = sub.get_text();

			file << text << std::endl << std::endl;
		}
	}

	/*
	 *
	 */
	Glib::ustring time_to_subrip(const SubtitleTime &t)
	{
		return build_message(
							"%02i:%02i:%02i,%03i",
							t.hours(), t.minutes(), t.seconds(), t.mseconds());
	}
};

#endif//_SubRip_h
