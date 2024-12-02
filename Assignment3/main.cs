// Program.cs
//
// CECS 342 Assignment 3
// File Type Report
// Solution Template

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;

namespace FileTypeReport {
  internal static class Program {
    // 1. Enumerate all files in a folder recursively
    private static IEnumerable<string> EnumerateFilesRecursively(string path) {
      foreach (var file in Directory.EnumerateFiles(path))
        {
            yield return file;
        }
        foreach (var dir in Directory.EnumerateDirectories(path))
        {
            foreach (var file in EnumerateFilesRecursively(dir))
            {
                yield return file;
            }
        }
    }

    // Human readable byte size
    private static string FormatByteSize(long byteSize) {
      double size = byteSize;
        string[] units = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB" };
        int unitIndex = 0;
        while (size >= 1000 && unitIndex < units.Length - 1)
        {
            size /= 1000;
            unitIndex++;
        }
        return $"{size:F2}{units[unitIndex]}";
    }

    // Create an HTML report file
    private static XDocument CreateReport(IEnumerable<string> files) {
      // 2. Process data
      var query =
        from file in files
        // TODO: Fill in your code here.
        select new {
          Type = fileGroup.Key, // file extension
          Count = fileGroup.Count(),
          TotalSize = totalSize
        };

      // 3. Functionally construct XML
      var alignment = new XAttribute("align", "right");
      var style = "table, th, td { border: 1px solid black; }";

      var tableRows = // TODO: Fill in your code here.
        
      var table = new XElement("table",
        new XElement("thead",
          new XElement("tr",
            new XElement("th", "Type"),
            new XElement("th", "Count"),
            new XElement("th", "Total Size"))),
        new XElement("tbody", tableRows));

      return new XDocument(
        new XDocumentType("html", null, null, null),
          new XElement("html",
            new XElement("head",
              new XElement("title", "File Report"),
              new XElement("style", style)),
            new XElement("body", table)));
    }

    // Console application with two arguments
    public static void Main(string[] args) {
      try {
        string inputFolder = args[0];
        string reportFile  = args[1];
        CreateReport(EnumerateFilesRecursively(inputFolder)).Save(reportFile);
      } catch {
        Console.WriteLine("Usage: FileTypeReport <folder> <report file>");
      }
    }
  }
}