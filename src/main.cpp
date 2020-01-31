#include <iostream>
#include <string>

#include <git2.h>

enum MainReturnCodes
{
	RETURN_SUCCESS,
	RETURN_WRONG_USAGE,
	RETURN_FAILED_TO_CLONE_REPO,
	RETURN_FAILED_TO_GET_REMOTE_BRANCHES,
	RETURN_FAILED_TO_ITERATE_REMOTE_BRANCHES
};

static void printUsage()
{
	std::cout << "./cppCodeFeaturesExtractor <git repo url> <local working directory> <output csv file name>" << std::endl;
}

static void printLibGit2LastError(int error)
{
	const git_error *e = giterr_last();
	std::cout << "Libgit2 error: error = " << error << ", klass = " << e->klass << ", message = " << e->message << std::endl;
}

int credentialsCallBack(git_cred** out, const char* url, const char* userFromUrl, unsigned int, void*)
{
	std::string user, pass;

	std::cout << "Please enter username to clone from " << url << " (" << userFromUrl << "):" << std::endl;
	std::cin >> user;
	std::cout << "Please enter password for " << user << ":" << std::endl;
	std::cin >> pass;

	return git_cred_userpass_plaintext_new(out, user.c_str(), pass.c_str());
}

int fetchProgressCallBack(const git_transfer_progress *stats, void *payload)
{
	auto fetchPercent = (100 * stats->received_objects) / stats->total_objects;
	auto indexPercent = (100 * stats->indexed_objects) / stats->total_objects;
	auto kiloBytes = stats->received_bytes / 1024;

	std::cout << "Fetch progress: network " << fetchPercent << "% (" << kiloBytes << " kb, " << stats->received_objects << "/" << stats->total_objects<< "), index " << indexPercent << "% (" << stats->indexed_objects << "/" << stats->total_objects << ")" << std::endl;

	return 0;
}


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printUsage();
		return RETURN_WRONG_USAGE;
	}

	git_libgit2_init();
	
	git_clone_options cloneOptions = GIT_CLONE_OPTIONS_INIT;
	cloneOptions.fetch_opts.callbacks.credentials = credentialsCallBack;
	cloneOptions.fetch_opts.callbacks.transfer_progress = fetchProgressCallBack;

	git_repository* repo = nullptr;
	int error = git_clone(&repo, argv[1], argv[2], &cloneOptions);
	if (error < 0)
	{
		printLibGit2LastError(error);
		git_libgit2_shutdown();
		return RETURN_FAILED_TO_CLONE_REPO;
	}

	git_branch_iterator* branchIt = nullptr;
	error = git_branch_iterator_new(&branchIt, repo, GIT_BRANCH_REMOTE);
	if (error < 0)
	{
		printLibGit2LastError(error);
		git_repository_free(repo);
		git_libgit2_shutdown();
		return RETURN_FAILED_TO_GET_REMOTE_BRANCHES;
	}

	git_reference* ref = nullptr;
	git_branch_t type;
	while ((error = git_branch_next(&ref, &type, branchIt)) == GIT_OK)
	{
		std::cout << "Libgit2 found remote branch " << git_reference_name(ref) << std::endl;
		git_reference_free(ref);
	}

	if (error < 0 && error != GIT_ITEROVER)
	{
		printLibGit2LastError(error);
		git_branch_iterator_free(branchIt);
		git_repository_free(repo);
		git_libgit2_shutdown();
		return RETURN_FAILED_TO_ITERATE_REMOTE_BRANCHES;
	}

	git_branch_iterator_free(branchIt);
	git_repository_free(repo);
	git_libgit2_shutdown();

	return RETURN_SUCCESS;
}