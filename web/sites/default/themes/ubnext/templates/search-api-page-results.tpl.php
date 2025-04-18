<?php
/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and the
 * child template are dependent on one another, sharing the markup for
 * definition lists.
 *
 * Note that modules and themes may implement their own search type and theme
 * function completely bypassing this template.
 *
 * Available variables:
 * - $index: The search index this search is based on.
 * - $result_count: Number of results.
 * - $spellcheck: Possible spelling suggestions from Search spellcheck module.
 * - $search_results: All results rendered as list items in a single HTML
 *   string.
 * - $items: All results as it is rendered through search-result.tpl.php.
 * - $search_performance: The number of results and how long the query took.
 * - $sec: The number of seconds it took to run the query.
 * - $pager: Row of control buttons for navigating between pages of results.
 * - $keys: The keywords of the executed search.
 * - $classes: String of CSS classes for search results.
 * - $page: The current Search API Page object.
 * - $no_results_help: Help text to display under the header if no results were
 *   found.
 *
 * View mode is set in the Search page settings. If you select
 * "Themed as search results", then the child template will be used for
 * theming the individual result. Any other view mode will bypass the
 * child template.
 *
 * @see template_preprocess_search_api_page_results()
 */

?>
<div class="<?php print $classes;?>">
  <?php if ($result_count): ?>
    <div class="search-meta"><strong><?php print t("Found !count of !max databases:", array('!count' => $result_count, '!max' => $variables['total-items-in-index'])); ?></strong></div>
  <?php endif; ?>
  <?php print render($spellcheck); ?>
  <?php if ($result_count): ?>
    <ol class="search-results list-unstyled">
      <li><?php print render($search_results); ?></li>
    </ol>
    <?php if(isset($show_all_link)): ?>
      <?php print $show_all_link; ?>
    <?php endif; ?>
  <?php else : ?>
    <div class="no-result"><?php print t('No database was found. Change your search and try again.');?></div>
  <?php endif; ?>
</div>
