﻿using System.IO;
using NUnit.Framework;
using UnitTests.Core;
using UnitTests.Runners;
using UnitTests.Validators;

namespace UnitTests
{
    [TestFixture]
    [Parallelizable(ParallelScope.Children)]
    public class PSharpBackendTests
    {
        [Test]
        public void TestCompilePSharpTemp()
        {
            var tempDir = Directory.CreateDirectory(Path.Combine(Constants.ScratchParentDirectory, "TestPSharpTemp"));
            var tempFilePath = new FileInfo(Path.Combine(Constants.SolutionDirectory, "tmp", "test.p"));
            //var foreignFilePath = new FileInfo(Path.Combine(Constants.SolutionDirectory, "tmp", "Foreign.cs"));

            if (!tempFilePath.Exists) return;

            var testCase = new CompilerTestCase(
                tempDir,
                new PSharpRunner(new[] {tempFilePath}),
                new CompileSuccessValidator());

            TestAssertions.AssertTestCase(testCase);
        }

        [Test]
        public void TestModuleSystem()
        {
            var tempDir = Directory.CreateDirectory(Path.Combine(Constants.ScratchParentDirectory, "TestPSharpTemp"));
            var tempFilePath =
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "Main.p"));
            var allFiles = new[]
            {
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "Main.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "PingPong.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "Safety.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "Liveness.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "PingPong", "Testscript.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "Env", "Env.p")),
                new FileInfo(Path.Combine(Constants.SolutionDirectory, "Tutorial", "Timer", "Timer.p"))
            };

            var testCase = new CompilerTestCase(
                tempDir,
                new PSharpRunner(allFiles),
                new CompileSuccessValidator());

            TestAssertions.AssertTestCase(testCase);
        }
    }
}