<?php

	/**
	 * @brief Converts four spaces to tabulation.
	 * @param $content The current content.
	 * @return std::string
	 */
	function convert_to_tabs (string $content): string
	{
		return str_replace('    ', "\t", $content);
	}

	/**
	 * @brief Removes brackets in local inclusions.
	 * @param $content The current content.
	 * @return std::string
	 */
	function remove_include_brackets (string $content): string
	{
		return preg_replace('#\#include <([^.>]+)\.hpp>#', '#include "$1.hpp"', $content);
	}

	/**
	 * @brief Removes the licence from the source file.
	 * @param $content The current content.
	 * @return std::string
	 */
	function rip_off_license (string $content, int $minStart = 64, int $maxLength = 512, string $startMask = '/*', string $endMask = '*/'): string
	{
		$start = strpos($content, $startMask);

		if ( $start >= 0 && $start < $minStart )
		{
			$stop = strpos($content, $endMask);

			if ( $stop > ($start + $maxLength) )
			{
				$content = substr($content, $stop + strlen($endMask));

				return trim($content) . PHP_EOL;
			}
		}

		return $content;
	}

	/**
	 * @brief Writes an up to date licence to the source file.
	 * @param $content The current content.
	 * @param $entry The file path in the project.
	 * @param $author The name of the author.
	 * @param $projectName The project name.
	 * @param $projectPlace The project place like a github location.
	 * @return std::string
	 */
	function write_gpl2_license (string $content, string $entry, string $author, string $projectName, string $projectPlace): string
	{
		$license =
'/*
 * ' . str_replace('./', '', $entry) . '
 * This file is part of ' . PROJECT_NAME . '
 *
 * Copyright (C) 2010-' . date('Y') . ' - ' . IDENTITY . '
 *
 * ' . PROJECT_NAME . ' is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ' . PROJECT_NAME . ' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ' . PROJECT_NAME . '; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * ' . PROJECT_PLACE . '
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */
' . PHP_EOL;

		return $license.$content;
	}

	/**
	 * @brief Writes an up to date licence to the source file.
	 * @param $content The current content.
	 * @param $entry The file path in the project.
	 * @param $author The name of the author.
	 * @param $projectName The project name.
	 * @param $projectPlace The project place like a github location.
	 * @return std::string
	 */
	function write_lgpl3_license (string $content, string $entry, string $author, string $projectName, string $projectPlace): string
	{
		$license =
'/*
 * ' . str_replace('./', '', $entry) . '
 * This file is part of ' . PROJECT_NAME . '
 *
 * Copyright (C) 2010-' . date('Y') . ' - ' . IDENTITY . '
 *
 * ' . PROJECT_NAME . ' is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * ' . PROJECT_NAME . ' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ' . PROJECT_NAME . '; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * ' . PROJECT_PLACE . '
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */
' . PHP_EOL;

		return $license.$content;
	}

	/**
	 * @brief Loops over each directory to apply transformations.
	 * @param $basePath The absolute path of the file in the system.
	 * @param $extensions An array of targeted file extensions.
	 * @param $exclusions An array of terms to find in a filepath to exclude the file from process.
	 * @param $licence
	 * @return int
	 */
	function crawl_directory (string $basePath, array $extensions, array $exclusions, string $licence = 'gpl2'): int
	{
		$count = 0;

		if ( $entries = glob($basePath . '/*') )
		{
		    print_r($entries);

			foreach ( $entries as $entry )
			{
			    /* NOTE: Excluded terms */
				foreach ( $exclusions as $exclusion )
				{
					if ( strstr($entry, $exclusion) !== false )
					{
					    continue 2;
					}
				}

				if ( is_dir($entry) )
				{
					$count += crawl_directory($entry, $extensions, $exclusions, $licence);

					continue;
				}

				if ( is_file($entry) === false )
				{
				    continue;
				}

				$tmp = explode('.', $entry);

				$ext = end($tmp);

				if ( in_array($ext, $extensions) === false )
				{
				    continue;
				}

				$count++;

				if ( $content = file_get_contents($entry) )
				{
					$updatedContent = rip_off_license($content);
					switch ( $licence )
					{
					    case 'gpl2' :
					        $updatedContent = write_gpl2_license($updatedContent, $entry, IDENTITY, PROJECT_NAME, PROJECT_PLACE);
					        break;

					    case 'lgpl3' :
					        $updatedContent = write_lgpl3_license($updatedContent, $entry, IDENTITY, PROJECT_NAME, PROJECT_PLACE);
					        break;

					    default:
					        break;
					}
					$updatedContent = convert_to_tabs($updatedContent);
					$updatedContent = remove_include_brackets($updatedContent);

					if ( $content === $updatedContent )
					{
						echo 'No change in file "' . $entry . '". Skipping ...' . PHP_EOL;

						continue;
					}

					if ( file_put_contents($entry, $updatedContent) === false )
					{
						echo 'Unable to write "' . $entry . '"' . PHP_EOL;

						exit(1);
					}
				}
				else
				{
					echo 'Unable to read "' . $entry . '"' . PHP_EOL;
				}
			}
		}

		return $count;
	}

?>
